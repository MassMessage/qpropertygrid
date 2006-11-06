//
// C++ Interface: test
//
// Description: 
//
//
// Author: ludo <ludo42fr@free.fr>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef TEST_H
#define TEST_H

 
class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3 &v);
 
	~Vector3();
 
	float getX() const;
	float getY() const;
	float getZ() const;
 
	void setX(float x);
	void setY(float y);
	void setZ(float z);
 
private:
	float m_x, m_y, m_z;
};
 

#include <QVariant>
Q_DECLARE_METATYPE(Vector3);


/////////////// pour gerer Vector3 dans les properties ;
#include "modelmanipulators/qvarianttoitem.h"

class Vector3ToItem : public QVariantToItem
{

public:

PropertyItem* fromQVariant(const QVariant&var,const QString &name="")const
{
if(!var.canConvert<Vector3>()) 
return 0;
Vector3 v3=var.value<Vector3>();
PropertyItem*parent=new PropertyGroupItem(name);
PropertyItem* ptr=new PropertyItem("X",parent);
ptr->setData(v3.getX());
ptr->setData(PropertyItem::valueEditorRole,PropertyIntSliderEditor::EDITOR_KEY);
 ptr=new PropertyItem("Y",parent);
ptr->setData(v3.getY());
ptr->setData(PropertyItem::valueEditorRole,PropertyIntSliderEditor::EDITOR_KEY);
ptr=new PropertyItem("Z",parent);
ptr->setData(v3.getZ());
ptr->setData(PropertyItem::valueEditorRole,PropertyIntSliderEditor::EDITOR_KEY);


return parent;
}

};









#endif