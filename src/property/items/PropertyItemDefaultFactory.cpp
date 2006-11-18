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
#include "items/PropertyItemDefaultFactory.h"
#include "items/PropertyItemProvider.h"

const QString PropertyItemDefaultFactory::K_DEFAULT_KEY="##DEFAULT##";



void PropertyItemDefaultFactory::onSingletonConstruct()
{

this->add<PropertyItemProvider>(K_DEFAULT_KEY,true);

/*
 switch ( variant.type() ) {
      case QVariant::Invalid:
      break;
      case QVariant::BitArray:
      break;
      case QVariant::Bitmap :
      break;
      case QVariant::Bool:
        return new PropertyItemBool(name,variant);
      break;
      case QVariant::Brush:
      break;
      case QVariant::ByteArray:
      break;
      case QVariant::Char:
      break;
      case QVariant::Color:
      break;
      case QVariant::Cursor:
      break;
      case QVariant::Date:
      break;
      case QVariant::DateTime:
      break;
      case QVariant::Double:
      break;
      case QVariant::Font:
      break;
      case QVariant::Icon :
      break;
      case QVariant::Image:
      break;
      case QVariant::Int:
      break;
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
      break;
      case QVariant::Point:
      break;
      case QVariant::PointF:
      break;
      case QVariant::Polygon :
      break;
      case QVariant::Rect:
      break;
      case QVariant::RectF:
      break;
      case QVariant::RegExp:
      break;
      case QVariant::Region:
      break;
      case QVariant::Size:
      break;
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
*/

};