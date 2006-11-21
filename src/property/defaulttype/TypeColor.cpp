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
#include "TypeColor.h"
#include "TypeInt.h"
#include <QApplication>
#include <QDebug>
#include <QStyleOptionButton>
#include <QColor>
PropertyItemColor::PropertyItemColor( QString name, const QVariant &value, PropertyItem *parent )
    : PropertyItemGroup( name, parent ) {
  setData( value );
  QColor color = data().value<QColor>();
  PropertyItem *it = new PropertyItemInt( "Red", color.red(), this );
  it->setMeta( true );
  connect( it, SIGNAL( dataChanged( QVariant ) ), this, SLOT( redChanged( QVariant ) ) );
  it = new PropertyItemInt( "Green", color.green(), this );
  it->setMeta( true );
  connect( it, SIGNAL( dataChanged( QVariant ) ), this, SLOT( greenChanged( QVariant ) ) );
  it = new PropertyItemInt( "Blue", color.blue(), this );
  it->setMeta( true );
  connect( it, SIGNAL( dataChanged( QVariant ) ), this, SLOT( blueChanged( QVariant ) ) );
  it = new PropertyItemInt( "Alpha", color.alpha(), this );
  it->setMeta( true );
  connect( it, SIGNAL( dataChanged( QVariant ) ), this, SLOT( alphaChanged( QVariant ) ) );
  setValueRenderer( PropertyRendererColor::K_ID );

  }
void PropertyItemColor::alphaChanged( QVariant newValue ) {
  QColor color = data().value<QColor>();
  color.setAlpha( newValue.toInt() );
  setData( PropertyItem::valueRole, color );

  }

void PropertyItemColor::blueChanged( QVariant newValue ) {
  QColor color = data().value<QColor>();
  color.setBlue( newValue.toInt() );
  setData( PropertyItem::valueRole, color );
  }

void PropertyItemColor::greenChanged( QVariant newValue ) {
  QColor color = data().value<QColor>();
  color.setGreen( newValue.toInt() );
  setData( PropertyItem::valueRole, color );

  }
void PropertyItemColor::redChanged( QVariant newValue ) {
  QColor color = data().value<QColor>();
  color.setRed( newValue.toInt() );
  setData( PropertyItem::valueRole, color );
  }

/////////////////////////////////////////////////////////////

const QString PropertyRendererColor::K_ID = "RENDER_COLOR_DEF";

PropertyRendererColor::PropertyRendererColor( QObject *parent )
    : PropertyRenderer( parent ) {}

void PropertyRendererColor::paintProperty ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex &index ) {
  static const int i = 15;
  PropertyItem *data = modelIndexToData( index );
  if ( data == 0 )
    return ;
  QRect rect = option.rect;
  QStyleOptionButton checkOption;
  QRect recColor = QRect( rect.left() + i / 2, rect.top() + ( rect.height() - i ) / 2, i, i );
  drawChecker( painter, recColor );
  painter->save();
  QColor col = data->data( PropertyItem::valueToRender ).value<QColor>();
  painter->setBrush( QColor( col ) );
  painter->setPen( QColor( 0, 0, 0 ) );
  painter->drawRect( recColor );
  painter->restore();

  rect.setLeft( rect.left() + 2 * i );
  QString text = "[ " + QString::number( col.red() ) + " ," + QString::number( col.green() ) + " ," + QString::number( col.blue() ) + " ," + QString::number( col.alpha() ) + " ]";
  text = option.fontMetrics.elidedText( text, Qt::ElideRight, rect.width() );
  painter->drawText( rect, text, QTextOption( Qt::AlignLeft ) );

  return ;

  }

void PropertyRendererColor::drawChecker( QPainter * painter, const QRect &rec, int oneElemSize ) const {
  static const QBrush checkerBrush[ 2 ] = {
                                            QBrush( QColor( 0, 0, 0 ) ), QBrush( QColor( 255, 255, 255 ) )
                                          };
  QRect prec( rec.left(), rec.top(), oneElemSize, oneElemSize );
  int index = 0;
  painter->save();
  painter->setPen( Qt::NoPen );
  while ( prec.top() < rec.bottom() ) {
    painter->setBrush( checkerBrush[ index ] );
    index = ( index == 0 ) ? 1 : 0;
    painter->drawRect( prec );
    prec.translate( oneElemSize, 0 );
    if ( prec.left() > rec.right() )
      prec.moveTo( rec.left(), prec.top() + oneElemSize );
    }
  painter->restore();

  }


QSize PropertyRendererColor::sizeHint( const QStyleOptionViewItem & option, const QModelIndex &index ) {
  return option.rect.size();
  }
