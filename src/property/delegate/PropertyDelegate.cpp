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
#include "delegate/PropertyDelegate.h"
#include <QModelIndex>


PropertyDelegate::PropertyDelegate( Factory<> *delegateFactory, QObject * parent )
    : QItemDelegate( parent )
,_factory(delegateFactory){
  //if(_factory==0)
//_factory=&PropertyDelegateFactory::instance();
  }

void PropertyDelegate::paint( QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
/*  PropertyRenderer * render = getRendererFor( index );
  if ( render == 0 )*/
    return QItemDelegate::paint( painter, option, index );
  //render->paintProperty( painter, option, index );
  }


QSize PropertyDelegate::sizeHint( const QStyleOptionViewItem & option, const QModelIndex & index ) const {
  /*PropertyRenderer * render = getRendererFor( index );
  if ( render == 0 )*/
    return QItemDelegate::sizeHint( option, index );
  //return render->sizeHint( option, index );
  }

QWidget * PropertyDelegate::createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
 /* PropertyEditor * edit = getEditorFor( index );
  if ( edit == 0 )*/
    return QItemDelegate::createEditor( parent, option, index );
  //return edit->createEditor( parent, option, index );
  }



void PropertyDelegate::updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
  //PropertyEditor * edit = getEditorFor( index );
  //if ( edit == 0 || !edit->provideUpdateGeometry() )
    return QItemDelegate::updateEditorGeometry( editor, option, index );
  //edit->updateEditorGeometry( editor, option, index );
  }

void PropertyDelegate::setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const {

  //PropertyEditor * edit = getEditorFor( index );
  //if ( edit == 0 )
    return QItemDelegate::setModelData( editor, model, index );
  //return edit->setModelData( editor, model, index );
  }

void PropertyDelegate::setEditorData( QWidget * editor, const QModelIndex & index ) const {


  //PropertyEditor * edit = getEditorFor( index );
  //if ( edit == 0 )
    return QItemDelegate::setEditorData( editor, index );
  //return edit->setEditorData( editor, index );
  }

PropertyItem * PropertyDelegate::toItem( const QModelIndex & index ) const {
  if ( !index.isValid() )
    return 0;
  return qobject_cast<PropertyItem *>( ( QObject* ) index.internalPointer() );
  }
/*

PropertyRenderer *PropertyDelegate::getRendererFor( const QModelIndex & index ) const {
  PropertyItem * data = toItem( index );
  if ( data == 0 )
    return 0;
  QVariant variant;
  if ( index.column() == 0 )
    variant = data->data( PropertyItem::nameRendererRole );
  else
    variant = data->data( PropertyItem::nameRendererRole );
  if ( !variant.isValid() || !variant.canConvert( QVariant::String ) )
    return 0;
  return _factory->get<PropertyRenderer>( variant.toString() );
  }



PropertyEditor *PropertyDelegate::getEditorFor( const QModelIndex & index ) const {
  PropertyItem * data = toItem( index );
  if ( data == 0 )
    return 0;
  QVariant variant = data->data( PropertyItem::valueEditorRole );
  if ( !variant.isValid() || !variant.canConvert( QVariant::String ) )
    return 0;
  return _factory->get<PropertyEditor>( variant.toString() );
  }
*/