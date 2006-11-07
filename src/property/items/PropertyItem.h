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
#ifndef PROPERTYITEM_H
#define PROPERTYITEM_H
#include <QObject>
#include <QVariant>
#include <QHash>
#include "core/TreeContainer.h"
#include "items/PropertyItemDefaultValueHolder.h"
class PropertyItem : public QObject , public TreeContainer<PropertyItem> {
    Q_OBJECT;
  protected:

    PropertyItemValueHolder *_valueHolder;
    int _columnCount;
    unsigned long _flags;
    QHash<int, QVariant> _data;
  public:

    enum propertyRoles{
      nameValueRole = Qt::UserRole,
      nameRendererRole,
      valueRole,
      valueRendererRole,
      valueEditorRole,
      endvalue
  };


    enum propertyDataFlags{
      flgValid = 0x1,
      flgData = 0x2,
      flgSection = 0x4,
      flgGroup = 0x8,
      flgHidden = 0x10,
      flgSystem = 0x20,
      flgRDOnly = 0x40,
      flgMeta = 0x80
  };

  public:

    PropertyItem( QString name = "", PropertyItem *parent = 0 ,PropertyItemValueHolder* setGet=new PropertyItemDefaultValueHolder());
    virtual ~PropertyItem();
    //manip des propietes
    QString name() const;
    void setName( QString name );
    int columnCount() const;
    void setColumnCount( int count );
    virtual QVariant data( int id= valueRole) const;
    void setData( const QVariant & );
    void setData( int id, const QVariant & );
    //manip des flags
    unsigned long flags() const;
    void setFlags( const unsigned long &fl );
    bool isValid() const;
    bool hasData() const;
    bool isVisible() const;
    bool isASection() const;
    bool isAGroup() const;
    bool isSystem() const;
    bool isReadonly() const;
    void setValid( bool );
    void setVisible( bool );
    void setSection( bool );
    void setGroup( bool );
    void setSystem( bool );
    void setReadOnly( bool );
  };



#endif

