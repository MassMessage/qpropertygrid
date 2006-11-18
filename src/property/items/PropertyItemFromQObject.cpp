/***************************************************************************
*   Copyright (C) 2006 by ludo   *
*   ludo42fr@free.fr   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
*                                                                         *
*   In addition, as a special exception, the copyright holders give       *
*   permission to link the code of this program with any edition of       *
*   the Qt library by Trolltech AS, Norway (or with modified versions     *
*   of Qt that use the same license as Qt), and distribute linked         *
*   combinations including the two.  You must obey the GNU General        *
*   Public License in all respects for all of the code used other than    *
*   Qt.  If you modify this file, you may extend this exception to        *
*   your version of the file, but you are not obligated to do so.  If     *
*   you do not wish to do so, delete this exception statement from        *
*   your version.                                                         *
***************************************************************************/
#include <QMetaProperty>
#include "items/PropertyItemDefaultFactory.h"
#include "items/PropertyItemFromQObject.h"
#include "items/PropertyItemProvider.h"
#include "items/PropertyItemQPropertyValueHolder.h"
#include "items/PropertyItemSection.h"
#include "items/PropertyItem.h"



PropertyItemFromQObject::PropertyItemFromQObject( Factory<>*fact, QObject *parent )
    : QObject( parent )
, _itemFactory( fact ) {}


void PropertyItemFromQObject::importPropertyForClass( const QObject *object, const QMetaObject *metaobject, PropertyItem*parent ) {
  if ( !metaobject )
    return ;
  importPropertyForClass( object, metaobject->superClass(), parent );
  PropertyItem *current = new PropertyItemSection( metaobject->className(), parent );
  for ( int i = 0;i < metaobject->propertyCount();i++ ) {
    QMetaProperty qmprop = metaobject->property( i );
    //on passe les proprietes aussi presentes dans la classe mere
    if ( metaobject->superClass() != 0 && metaobject->superClass() ->indexOfProperty( qmprop.name() ) > -1 )
      continue;
    //on passe aussi les non storable -> je comprends pas comment on s'en sert
    if ( !qmprop.isStored() )
      continue;
    buildPropertyItem( object, qmprop, current );

    }

  }

PropertyItem* PropertyItemFromQObject::buildPropertyItem( const QObject *object, QMetaProperty &qmprop, PropertyItem *parent ) {
  PropertyItem * prop = 0;
  if ( _itemFactory && qmprop.read( object ).isValid() ) {
    QString key = qmprop.read( object ).typeName();
    PropertyItemProvider *itemProvider = _itemFactory->get
                                         <PropertyItemProvider>( key );
    if ( itemProvider == 0 )   //on tente de recuperer le provider par defaut
      itemProvider = _itemFactory->get
                     <PropertyItemProvider>( PropertyItemDefaultFactory::K_DEFAULT_KEY );
    if ( itemProvider != 0 )
      prop = itemProvider->fromQVariant( qmprop.name(), qmprop.read( object ), parent );
    }
  //si 0 c'est que la creation depuis la factory a echoue
  if ( prop == 0 ) {
    //on cree par defaut
    prop = new PropertyItem( qmprop.name(), parent );
    prop->setData( qmprop.read( object ) );
    }

  return prop;

  }


PropertyItem* PropertyItemFromQObject::importFrom( const QObject *obj, PropertyItem*parent, bool createSection ) {
  if ( obj == 0 )
    return parent;
  if ( parent == 0 )
    createSection = true;
  if ( createSection )
    parent = new PropertyItemSection( obj->objectName(), parent );
  importPropertyForClass( obj, obj->metaObject(), parent );
  return parent;
  }






