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
#include "items/PropertyItemQPropertyValueHolder.h"
#include "items/PropertyItem.h"
#include <QStringList>
#include <QDebug>
PropertyItemQPropertyValueHolder::PropertyItemQPropertyValueHolder( QMetaProperty property, QObject *object )
    : PropertyItemValueHolder()
    , _meta( property )
, _object( object ) {


  if ( _meta.isEnumType() ) {
    _table->addToTable( _meta.enumerator() );
    _table->setValid( true );
    }

  if ( _meta.isFlagType() ) {
    setTranslationTable( PropertyItemFlagTable() );
    _table->addToTable( _meta.enumerator() );
    _table->setValid( true );
    }


  }

PropertyItemQPropertyValueHolder::PropertyItemQPropertyValueHolder( const PropertyItemQPropertyValueHolder& copy )
    : PropertyItemValueHolder()
    , _meta( copy._meta )
, _object( copy._object ) {
  }
PropertyItemQPropertyValueHolder::~PropertyItemQPropertyValueHolder() {}
void PropertyItemQPropertyValueHolder::set( const PropertyItem *item, const QVariant &value ) {
  qDebug() << item->name() << " try write";
  if ( _object && _meta.isWritable() )
    _meta.write( _object, value );
  else
    qDebug() << item->name() << " Is not writable";
  }


QVariant PropertyItemQPropertyValueHolder::get( const PropertyItem *item ) {
  if ( _object )
    return _meta.read( _object );
  return QVariant();
  }



QVariant PropertyItemQPropertyValueHolder::getForRenderer( const PropertyItem *item ) {

  if ( item == 0 )
    return "";
  if ( item->isAGroup() ) {
    QStringList lst;
    for ( int i = 0;i < item->childCount();i++ ) {
      PropertyItem *child = item->childAt( i );
      if ( child == 0 )
        continue;
      if ( !child->isGroupCollectable() )
        continue;
      QVariant val = child ->data( PropertyItem::valueToRender );
      if ( val.canConvert( QVariant::String ) )
        lst .push_back( val.toString() );
      else
        lst .push_back( "..." );
      }
    return QString( "[ " ) + lst.join( " ," ) + " ]";
    }

  return PropertyItemValueHolder::getForRenderer( item );

  }

