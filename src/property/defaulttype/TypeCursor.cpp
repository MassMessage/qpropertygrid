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
#include "defaulttype/TypeCursor.h"
#include "defaulttype/TypeInt.h"
#include <QDebug>
#include <QBitmap>
PropertyItemCursor::PropertyItemCursor( QString name, const QVariant &value, PropertyItem *parent )
    : PropertyItemGroup( name, parent ) {
  setData( PropertyItem::valueRole, value );
  setValueRenderer( PropertyRendererCursor::K_ID );
  }





////////////////////////////////
const QString PropertyRendererCursor::K_ID = "RENDER_CURSOR_DEF";

PropertyRendererCursor::PropertyRendererCursor( QObject *parent )
    : PropertyRenderer( parent ) {}

void PropertyRendererCursor::paintProperty ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex &index ) {

  static const int i = 25;
  PropertyItem *data = modelIndexToData( index );
  if ( data == 0 )
    return ;

  QVariant cursorVariant = data->data();
  if ( !cursorVariant.canConvert( QVariant::Cursor ) )
    return ;

  QCursor cursor = cursorVariant.value<QCursor>();


  QRect rect = option.rect;
  QRect pixRec = QRect( rect.left() + i / 2, rect.top() + ( rect.height() - i ) / 2, i, i );
  QPixmap pix = getCursorPixmap( cursor );
  painter->drawPixmap( pixRec, pix );

  }

QSize PropertyRendererCursor::sizeHint( const QStyleOptionViewItem & option, const QModelIndex &index ) {
  return QSize(28,28);
      //option.rect.size();
  }


QPixmap PropertyRendererCursor::getCursorPixmap( const QCursor &cursor ) {
  static bool wasInit=false;
  QPixmap cursorPixmap = cursor.pixmap();
  if ( !cursorPixmap.isNull() )
    return cursorPixmap;

  if ( cursor.bitmap() != 0 )
    return QBitmap( *cursor.bitmap() );


    if(!wasInit)
    {
     Q_INIT_RESOURCE(property);
       wasInit=true;
    }
  switch ( cursor.shape() ) {
      case Qt::ArrowCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/arrow.png" ) );
      case Qt::UpArrowCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/uparrow.png" ) );
      case Qt::CrossCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/cross.png" ) );
      case Qt::WaitCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/wait.png" ) );
      case Qt::IBeamCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/ibeam.png" ) );
      case Qt::SizeVerCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/sizev.png" ) );
      case Qt::SizeHorCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/sizeh.png" ) );
      case Qt::SizeBDiagCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/sizef.png" ) );
      case Qt::SizeFDiagCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/sizeb.png" ) );
      case Qt::SizeAllCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/sizeall.png" ) );
      case Qt::BlankCursor: {
        QBitmap cur = QBitmap( 25, 25 );
        cur.clear();
        return cur;
        }
      case Qt::SplitVCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/vsplit.png" ) );
      case Qt::SplitHCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/hsplit.png" ) );
      case Qt::PointingHandCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/hand.png" ) );
      case Qt::ForbiddenCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/no.png" ) );
      case Qt::WhatsThisCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/whatsthis.png" ) );
      case Qt::BusyCursor:
      return QPixmap( QString::fromUtf8( ":/property/images/cursors/busy.png" ) );
      default:
      return QPixmap();
    }
  }


