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
#include "delegate/renderers/PropertyRendererGroup.h"
#include <QApplication>
#include <QPaintDevice>

const QString PropertyRendererGroup::K_ID="RENDER_GROUP_DEF";

PropertyRendererGroup::PropertyRendererGroup( QObject *parent )
    : PropertyRenderer( parent ) {

  }

void PropertyRendererGroup::paintProperty ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex &index  ) {
static const int i = 9;
PropertyItem *data=modelIndexToData(index);
        if(data==0)
          return;
        QStyleOptionViewItem opt=option;
        QRect r = opt.rect;
        QRect textrect =r;
//QRect(r.left() + i*2, r.top(), r.width() - ((5*i)/2), r.height());
        opt.font.setBold( true);
        QString text = opt.fontMetrics.elidedText(data->name(), Qt::ElideMiddle, textrect.width());
        painter->save();
        painter->setFont( opt.font);
        painter->drawText(textrect,text,QTextOption( Qt::AlignLeft));
        painter->restore();

}


QSize PropertyRendererGroup::sizeHint( const QStyleOptionViewItem & option, const QModelIndex &index  ) {
return option.rect.size();
  }

