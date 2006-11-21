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
#ifndef DEFAULTITEMCOLOR_H
#define DEFAULTITEMCOLOR_H
#include "items/PropertyItemGroup.h"
#include "items/PropertyItemProvider.h"
#include "delegate/PropertyRenderer.h"

class PropertyItemColor : public PropertyItemGroup {
    Q_OBJECT;

  public:
    PropertyItemColor( QString name, const QVariant &value = QVariant(), PropertyItem *parent = 0 );
  public slots:
    void alphaChanged( QVariant newvalue );
    void blueChanged( QVariant newvalue );
    void greenChanged( QVariant newvalue );
    void redChanged( QVariant newvalue );
  };


class PropertyRendererColor : public PropertyRenderer {
    Q_OBJECT;
  protected:
    void drawChecker(QPainter * painter,const QRect &rec,int oneElemSize=3) const;
  public:
    PropertyRendererColor( QObject *parent = 0 );
    virtual void paintProperty ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex &index = QModelIndex() );
    virtual QSize sizeHint( const QStyleOptionViewItem & option, const QModelIndex &index = QModelIndex() );

    static const QString K_ID;
  };

#endif
