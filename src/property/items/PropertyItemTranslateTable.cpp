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
#include "PropertyItemTranslateTable.h"
#include "QStringList"
#include <QDebug>

PropertyItemTranslateTable::PropertyItemTranslateTable()
    : QObject( 0 )
    , _translation()
    , _defaultValue()
    , _defaultKey()
    , _keyToValuePolicy( EPass )
    , _valueToKeyPolicy( EPass )
    , _enabled( true )
, _valid( false ) {}


PropertyItemTranslateTable::PropertyItemTranslateTable( const PropertyItemTranslateTable&other )
    : QObject( 0 )
    , _translation( other._translation )
    , _defaultValue( other._defaultValue )
    , _defaultKey( other._defaultKey )
    , _keyToValuePolicy( other._keyToValuePolicy )
    , _valueToKeyPolicy( other._valueToKeyPolicy )
    , _enabled( other._enabled )
, _valid( other._valid ) {}
PropertyItemTranslateTable::~PropertyItemTranslateTable() {}
QVariant PropertyItemTranslateTable::keyFromValue( QVariant value ) const {
  for ( int i = 0;i < _translation.size();i++ )
    if ( _translation[ i ].value == value )
      return _translation[ i ].key;
  switch ( _valueToKeyPolicy ) {
      case EInvalid:
      return QVariant();
      case EPass:
      return value;
      case EReturnDefault:
      return defaultKey();
      default:
      return QVariant();
    }
  //normalement on n'arrive jamais la, mais bon
  return QVariant();
  }

QVariant PropertyItemTranslateTable::keyToValue( QVariant key ) const {
  for ( int i = 0;i < _translation.size();i++ )
    if ( _translation[ i ].key == key )
      return _translation[ i ].value;
  switch ( _keyToValuePolicy ) {
      case EInvalid:
      return QVariant();
      case EPass:
      return key;
      case EReturnDefault:
      return defaultValue();
      default:
      return QVariant();
    }
  //normalement on n'arrive jamais la, mais bon
  return QVariant();
  }


void PropertyItemTranslateTable::addToTable( const QMetaEnum&enumToAdd ) {
  for ( int i = 0;i < enumToAdd.keyCount();i++ )
    addToTable( enumToAdd.value( i ), enumToAdd.key( i ) );
  }
void PropertyItemTranslateTable::addToTable( const QVariant &value, const QVariant &key ) {
  qDebug() << "Adding to table " << value << " -> " << key;
  for ( int i = 0;i < _translation.size();i++ )
    if ( _translation[ i ].value == value ) {
      _translation[ i ].key = key;
      return ;
      }
  SValKey val;
  val.key = key;
  val.value = value;
  _translation.append( val );
  }

bool PropertyItemTranslateTable::hasDefaultValue() const {
  return _defaultValue.isValid();
  }
void PropertyItemTranslateTable::setDefaultValue( const QVariant&defaultValue ) {
  _defaultValue = defaultValue;
  }
QVariant PropertyItemTranslateTable::defaultValue() const {
  return _defaultValue;
  }

bool PropertyItemTranslateTable::hasDefaultKey() const {

  return _defaultKey.isValid();
  }
void PropertyItemTranslateTable::setDefaultKey( const QVariant&defaultKey ) {
  _defaultKey = defaultKey;
  }

QVariant PropertyItemTranslateTable::defaultKey() const {
  return _defaultKey;
  }

void PropertyItemTranslateTable::removeValue( const QVariant &value ) {
  for ( int i = 0;i < _translation.size();i++ )
    if ( _translation[ i ].value == value ) {
      _translation.removeAt( i );
      return ;
      }
  }

bool PropertyItemTranslateTable::hasValue( const QVariant &value ) {
  for ( int i = 0;i < _translation.size();i++ )
    if ( _translation[ i ].value == value )
      return true;
  return false;
  }
void PropertyItemTranslateTable::setKeyToValuePolicy( translationPolicy policy ) {
  _keyToValuePolicy = policy;
  }
int PropertyItemTranslateTable::keyToValuePolicy() const {
  return _keyToValuePolicy;
  }
void PropertyItemTranslateTable::setValueToKeyPolicy( translationPolicy policy ) {
  _valueToKeyPolicy = policy;
  }
int PropertyItemTranslateTable::valueToKeyPolicy() const {
  return _valueToKeyPolicy;
  }
bool PropertyItemTranslateTable::enabled() const {
  return _enabled;
  }
void PropertyItemTranslateTable::setEnable( bool enable ) {
  _enabled = enable;
  }
bool PropertyItemTranslateTable::valid() const {
  return _valid;
  }
void PropertyItemTranslateTable::setValid( bool valid ) {
  _valid = valid;
  }


////////////////////////////////:


PropertyItemFlagTable::PropertyItemFlagTable()
    : PropertyItemTranslateTable() {}
PropertyItemFlagTable::PropertyItemFlagTable( const PropertyItemFlagTable&other )
    : PropertyItemTranslateTable( other ) {}
PropertyItemFlagTable::~PropertyItemFlagTable() {}

QVariant PropertyItemFlagTable::keyFromValue( QVariant value ) const {
  QString retValue = "";
  if ( !value.canConvert( QVariant::UInt ) )
    return QVariant();
  unsigned int ivalue = value.toUInt();
  for ( int i = 0;i < _translation.size();i++ ) {
    if ( !_translation[ i ].value.canConvert( QVariant::UInt ) )
      continue;
    if ( ivalue & _translation[ i ].value.toUInt() && _translation[ i ].key.canConvert( QVariant::String ) ) {
      if ( retValue.length() )
        retValue += " | ";
      retValue += _translation[ i ].key.toString();
      }
    return retValue;
    }



  }

QVariant PropertyItemFlagTable::keyToValue( QVariant key ) const {
  if ( !key.canConvert( QVariant::String ) )
    return QVariant();
  QStringList lst = key.toString().split ( "|", QString::SkipEmptyParts );
  unsigned int value = 0;
  for ( int i = 0;i < lst.size();i++ ) {
    QString flg = lst[ i ].trimmed();
    bool found = false;
    for ( int j = 0;j < _translation.size();j++ ) {
      if ( _translation[ j ].key == flg && _translation[ j ].value.canConvert( QVariant::UInt ) ) {
        value |= _translation[ j ].value.toUInt();
        found = true;
        break;
        }
      }
    if ( !found )
      return QVariant();
    }
  return value;

  }



void PropertyItemFlagTable::addToTable( const QVariant &value, const QVariant &key ) {
  PropertyItemTranslateTable::addToTable( value, key );
  qSort( _translation );

  }



