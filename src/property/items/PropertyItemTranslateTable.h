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
#ifndef PROPERTYITEMTRANSLATETABLE_H
#define PROPERTYITEMTRANSLATETABLE_H

#include <QObject>
#include <QMetaEnum>
#include <QVariant>
#include <QList>
#include "PropertyItemValueChecker.h"
class PropertyItemTranslateTable : public PropertyItemValueChecker {

  public:
    enum translationPolicy{
      EInvalid,
      EPass,
      EReturnDefault
  };
  protected:
    class SValKey {
      public:
        QVariant value;
        QVariant key;
        bool operator<( const SValKey&other ) const {
          if ( value.canConvert( QVariant::UInt ) && other.value.canConvert( QVariant::UInt ) )
            return value.toUInt() < value.toUInt();
          if ( value.canConvert( QVariant::String ) && other.value.canConvert( QVariant::String ) )
            return value.toString() < value.toString();
          return false;
          }
      };

    QList<SValKey> _translation;
    QVariant _defaultValue;
    QVariant _defaultKey;
    translationPolicy _keyToValuePolicy;
    translationPolicy _valueToKeyPolicy;

  public:
    PropertyItemTranslateTable();
    PropertyItemTranslateTable( const PropertyItemTranslateTable&other );
    virtual ~PropertyItemTranslateTable();
    virtual QVariant checkoutValue( const QVariant&, bool internal = false ) const;
    virtual QVariant checkinValue( const QVariant& ) const;
    virtual void addToTable( const QMetaEnum&enumToAdd );
    virtual void addToTable( const QVariant &value, const QVariant &key );
    bool hasDefaultValue() const;
    void setDefaultValue( const QVariant&defaultValue = QVariant() );
    QVariant defaultValue() const;
    bool hasDefaultKey() const;
    void setDefaultKey( const QVariant&defaultKey = QVariant() );
    QVariant defaultKey() const;
    void removeValue( const QVariant &value );
    bool hasValue( const QVariant &value );
    void setKeyToValuePolicy( translationPolicy policy );
    int keyToValuePolicy() const;
    void setValueToKeyPolicy( translationPolicy policy );
    int valueToKeyPolicy() const;

  };


class PropertyItemFlagTable : public PropertyItemTranslateTable {

  public:
    PropertyItemFlagTable();
    PropertyItemFlagTable( const PropertyItemFlagTable&other );
    virtual ~PropertyItemFlagTable();

 virtual QVariant checkoutValue( const QVariant&, bool internal = false ) const;
    virtual QVariant checkinValue( const QVariant& ) const;
    virtual void addToTable( const QVariant &value, const QVariant &key );
    virtual void addToTable(const QMetaEnum&enumToAdd){PropertyItemTranslateTable::addToTable(enumToAdd);};

  };
#endif
