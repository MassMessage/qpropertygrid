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
#include "TypePixmap.h"
#include <QApplication>
#include <QDebug>
 #include <QStyleOptionButton>
#include <QColor>
#include <QBitmap>

PropertyItemPixmap::PropertyItemPixmap( QString name, const QVariant &value, PropertyItem *parent )
    : PropertyItem( name, parent ) {
  setData( value );
  setValueRenderer( PropertyRendererPixmap::K_ID );
  }


/////////////////////////////////////////////////////////////

const QString PropertyRendererPixmap::K_ID = "RENDER_PIXMAP_DEF";

PropertyRendererPixmap::PropertyRendererPixmap( QObject *parent )
    : PropertyRenderer( parent ) {
  }

void PropertyRendererPixmap::paintProperty ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex &index ) {
  static const int i = 16;
  PropertyItem *data = modelIndexToData( index );
  if ( data == 0 )
    return ;
  QRect rect = option.rect;
  QRect pixRec = QRect( rect.left() + i / 2, rect.top() + ( rect.height() - i ) / 2, i, i );
  QPixmap pix = getPixmapFromQVariant( data->data() );
  painter->drawPixmap( pixRec, pix );
  }



QPixmap PropertyRendererPixmap::getPixmapFromQVariant( const QVariant&px ) const {
  switch ( px.type() ) {
      case QVariant::Bitmap:
      return px.value<QBitmap>();
      case QVariant::Image:
      return QPixmap::fromImage( px.value<QImage>() );
      case QVariant::Pixmap:
      return px.value<QPixmap>();
      default:
      return QPixmap();
    }
  return QPixmap(); //<- on ne devrait jamais arriver la ;)

  }

QSize PropertyRendererPixmap::sizeHint( const QStyleOptionViewItem & option, const QModelIndex &index ) {
  return option.rect.size();
  }
