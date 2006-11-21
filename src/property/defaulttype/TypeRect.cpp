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
#include "defaulttype/TypeRect.h"
#include "defaulttype/TypeInt.h"
#include <QDebug>
PropertyItemRect::PropertyItemRect( QString name, const QVariant &value, PropertyItem *parent )
:PropertyItemGroup(name,parent) {
setData(PropertyItem::valueRole,value);
QRect rec=data().toRect();
PropertyItem *it=new PropertyItemInt("X",rec.x(),this);
it->setMeta(true);
connect(it,SIGNAL(dataChanged(QVariant)),this,SLOT(onXChange(QVariant)));
it=new PropertyItemInt("Y",rec.y(),this);
it->setMeta(true);
connect(it,SIGNAL(dataChanged(QVariant)),this,SLOT(onYChange(QVariant)));
it=new PropertyItemInt("Width",rec.width(),this);
it->setMeta(true);
connect(it,SIGNAL(dataChanged(QVariant)),this,SLOT(onWidthChange(QVariant)));
it=new PropertyItemInt("Height",rec.height(),this);
it->setMeta(true);
connect(it,SIGNAL(dataChanged(QVariant)),this,SLOT(onHeightChange(QVariant)));
}


void PropertyItemRect::onXChange(QVariant newValue)
{
QRect rec=data().toRect();
rec.setX(newValue.toInt());
setData(PropertyItem::valueRole,rec);
}

void PropertyItemRect::onYChange(QVariant newValue)
{
QRect rec=data().toRect();
rec.setY(newValue.toInt());
setData(PropertyItem::valueRole,rec);
}


void PropertyItemRect::onWidthChange(QVariant newValue)
{
QRect rec=data().toRect();
rec.setWidth(newValue.toInt());
setData(PropertyItem::valueRole,rec);
}

void PropertyItemRect::onHeightChange(QVariant newValue)
{
QRect rec=data().toRect();
rec.setHeight(newValue.toInt());
setData(PropertyItem::valueRole,rec);
}
