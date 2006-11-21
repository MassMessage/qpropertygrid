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
#include "PropertyItemProvider.h"
#include "defaulttype/TypeBool.h"
#include "defaulttype/TypeSize.h"
#include "defaulttype/TypeRect.h"
#include "defaulttype/TypeInt.h"
#include "defaulttype/TypeFont.h"
#include "defaulttype/TypeCursor.h"
#include "defaulttype/TypeColor.h"
#include "defaulttype/TypePixmap.h"
PropertyItem* PropertyItemProvider::fromQVariant( const QString &name, const QVariant&value, PropertyItem *parent ) const {
  switch ( value.type() ) {
      case QVariant::Invalid:
      break;
      case QVariant::BitArray:
      break;
      case QVariant::Bitmap :
       return new PropertyItemPixmap( name, value, parent );
      break;
      case QVariant::Bool:
      return new PropertyItemBool( name, value, parent );
      case QVariant::Brush:
      break;
      case QVariant::ByteArray:
      break;
      case QVariant::Char:
      break;
      case QVariant::Color:
      return new PropertyItemColor(name, value, parent );
      case QVariant::Cursor:
      return new PropertyItemCursor(name, value, parent );
      case QVariant::Date:
      break;
      case QVariant::DateTime:
      break;
      case QVariant::Double:
      break;
      case QVariant::Font:
      return new PropertyItemFont(name, value, parent );
      case QVariant::Icon :
         return new PropertyItemPixmap( name, value, parent );
      break;
      case QVariant::Image:
         return new PropertyItemPixmap( name, value, parent );
      break;
      case QVariant::Int:
      return new PropertyItemInt(name, value, parent );
      case QVariant::KeySequence:
      break;
      case QVariant::Line:
      break;
      case QVariant::LineF:
      break;
      case QVariant::List:
      break;
      case QVariant::Locale:
      break;
      case QVariant::LongLong:
      break;
      case QVariant::Map:
      break;
      case QVariant::Matrix:
      break;
      case QVariant::Palette:
      break;
      case QVariant::Pen:
      break;
      case QVariant::Pixmap:
         return new PropertyItemPixmap( name, value, parent );
      break;
      case QVariant::Point:
      break;
      case QVariant::PointF:
      break;
      case QVariant::Polygon :
      break;
      case QVariant::Rect:
      return new PropertyItemRect(name, value, parent );
      case QVariant::RectF:
      break;
      case QVariant::RegExp:
      break;
      case QVariant::Region:
      break;
      case QVariant::Size:
      return new PropertyItemSize(name, value, parent );
      case QVariant::SizeF:
      break;
      case QVariant::SizePolicy:
      break;
      case QVariant::String:
      break;
      case QVariant::StringList:
      break;
      case QVariant::TextFormat:
      break;
      case QVariant::TextLength:
      break;
      case QVariant::Time:
      break;
      case QVariant::UInt:
      break;
      case QVariant::ULongLong:
      break;
      case QVariant::Url:
      break;
      case QVariant::UserType :
      break;
      default:
      break;

    }


  return 0;

  }



