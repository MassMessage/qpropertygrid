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
#include "defaulttype/TypeFont.h"
#include "defaulttype/TypeInt.h"
//#include "defaulttype/TypeString.h"
#include "defaulttype/TypeBool.h"
#include <QFont>
#include <QDebug>
PropertyItemFont::PropertyItemFont( QString name, const QVariant &value, PropertyItem *parent )
    : PropertyItemGroup( name, parent ) {
  setData( PropertyItem::valueRole, value );
  QFont ft = value.value<QFont>();
  PropertyItem *it; /*=new PropertyItemString("Family",ft.family(),this);*/
  it = new PropertyItemInt( "Size", ft.pointSize(), this );
  it->setMeta( true );
  connect( it, SIGNAL( dataChanged( QVariant ) ), this, SLOT( onSizeChange( QVariant ) ) );
  it = new PropertyItemBool( "Bold", ft.bold(), this );
  it->setMeta( true );
  it->setGroupCollectable(false);
  connect( it, SIGNAL( dataChanged( QVariant ) ), this, SLOT( onBoldChange( QVariant ) ) );
  it = new PropertyItemBool( "Italic", ft.italic(), this );
  it->setMeta( true );
it->setGroupCollectable(false);
  connect( it, SIGNAL( dataChanged( QVariant ) ), this, SLOT( onItalicChange( QVariant ) ) );
  it = new PropertyItemBool( "Underline", ft.underline(), this );
  it->setMeta( true );
  it->setGroupCollectable(false);
  connect( it, SIGNAL( dataChanged( QVariant ) ), this, SLOT( onUnderlineChange( QVariant ) ) );
  it = new PropertyItemBool( "Strikeout", ft.strikeOut(), this );
  it->setMeta( true );
  it->setGroupCollectable(false);
  connect( it, SIGNAL( dataChanged( QVariant ) ), this, SLOT( onStrikeoutChange( QVariant ) ) );
  it = new PropertyItemBool( "Kerning", ft.kerning(), this );
  it->setMeta( true );
  it->setGroupCollectable(false);
  connect( it, SIGNAL( dataChanged( QVariant ) ), this, SLOT( onKerningChange( QVariant ) ) );
  it = new PropertyItemBool( "Antialiasing", ( ft.styleStrategy() == QFont::PreferAntialias ) , this );
  it->setMeta( true );
  it->setGroupCollectable(false);
  connect( it, SIGNAL( dataChanged( QVariant ) ), this, SLOT( onAntialiasChange( QVariant ) ) );
  }


void PropertyItemFont::onSizeChange( QVariant newValue ) {

  QFont ft = data().value<QFont>();
  ft.setPointSize( newValue.toInt( ) );
  setData( PropertyItem::valueRole, ft );

  }
void PropertyItemFont::onBoldChange( QVariant newValue ) {
  QFont ft = data().value<QFont>();
  ft.setBold( newValue.toBool() );
  setData( PropertyItem::valueRole, ft );
  }
void PropertyItemFont::onItalicChange( QVariant newValue ) {
  QFont ft = data().value<QFont>();
  ft.setItalic( newValue.toBool() );
  setData( PropertyItem::valueRole, ft );
  }
void PropertyItemFont::onUnderlineChange( QVariant newValue ) {
  QFont ft = data().value<QFont>();
  ft.setUnderline( newValue.toBool() );
  setData( PropertyItem::valueRole, ft );
  }
void PropertyItemFont::onStrikeoutChange( QVariant newValue ) {
  QFont ft = data().value<QFont>();
  ft.setStrikeOut( newValue.toBool() );
  setData( PropertyItem::valueRole, ft );
  }
void PropertyItemFont::onKerningChange( QVariant newValue ) {
  QFont ft = data().value<QFont>();
  ft.setKerning( newValue.toBool() );
  setData( PropertyItem::valueRole, ft );
  }
void PropertyItemFont::onAntialiasChange( QVariant newValue ) {
  QFont ft = data().value<QFont>();
  if ( newValue.toBool() )
    ft.setStyleStrategy( QFont::PreferAntialias );
  else
    ft.setStyleStrategy( QFont::NoAntialias );
  setData( PropertyItem::valueRole, ft );
  }




/*
void PropertyItemSize::onWidthChange(QVariant newValue)
  {
qDebug()<<"Width change";
QSize sz=data().toSize();
sz.setWidth(newValue.toInt());
setData(PropertyItem::valueRole,sz);
  }

void PropertyItemSize::onheigthChange(QVariant newValue)
  {
QSize sz=data().toSize();
sz.setHeight(newValue.toInt());
setData(PropertyItem::valueRole,sz);

  }

*/
