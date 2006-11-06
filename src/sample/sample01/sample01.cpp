#include "PropertyModel.h"

#include <QtGui>
#include <QTreeView>
#include "propertydelegate.h"
#include "propertydelegatefactory.h"
#include "propertyrenderer.h"
#include "propertyflatview.h"


#include "propertyitems/propertysectionitem.h"
#include "propertyitems/propertygroupitem.h"
#include "propertyeditors/propertyintslidereditor.h"
#include "propertyrenderers/propertycolorrenderer.h"
#include "modelmanipulators/qobjectimporter.h"



#include "test.h"



int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    PropertyModel *model=new PropertyModel();
    //on enregsitre le vector3 dans la factory statique
    // c'est mal fait de mettre le nom en dur, mais bon ca marche
    QPropertyToItemFactory::instance().add<Vector3ToItem>("Vector3");


    //un petit test
    Vector3 v3;
    v3.setZ(42.0); //hihi encore un ;)
    QVariant v3Variant;
    v3Variant.setValue(v3);



    QVariantToItem *convitem=QPropertyToItemFactory::instance().get<QVariantToItem>(v3Variant.typeName());
    if(convitem!=0)
        model->add
        (convitem->fromQVariant(v3Variant,"Bah, un test de vector3"));
//////////////////////////////////////////


    PropertyDelegateFactory::instance().add<StdRender>(NO_EDITOR_KEY,true);

    PropertyItem *se=model->add
                     (new PropertySectionItem("section01"));
    PropertyItem *ptr=new PropertyItem("string (defaut editor/readonly)",se);
    ptr->setData("une string");
    ptr->setReadOnly(true);
    ptr=new PropertyItem("couleur (defaut editor/defaut render)",se);
    ptr->setData(QColor(0,255,0));
    ptr->setData(PropertyItem::valueRendererRole,PropertyColorRenderer::RENDER_KEY);
    ptr=new PropertyItem("int (slider editor/section render)",se);
    ptr->setData(0);
    ptr->setData(PropertyItem::minIntRole,-42);
    ptr->setData(PropertyItem::maxIntRole,42);
    ptr->setData(PropertyItem::valueEditorRole,PropertyIntSliderEditor::EDITOR_KEY);


    se=model->add
       (new PropertyGroupItem("GROUP01"));
    ptr=new PropertyItem("test",se);
    ptr->setData("unevaleur");
    ptr=new PropertyItem("test01",se);
    ptr->setData("42");
    ptr->setData(PropertyItem::valueEditorRole,PropertyIntSliderEditor::EDITOR_KEY);

    se=new PropertyGroupItem("SOUSGROUP 01",se);
    ptr=new PropertyItem("test",se);
    ptr->setData("AAAAAAA");
    ptr=new PropertyItem("val",se);
    ptr->setData("0000999");
    ptr->setData(PropertyItem::valueEditorRole,PropertyIntSliderEditor::EDITOR_KEY);
    ptr->setData(PropertyItem::minIntRole,42);
    ptr->setData(PropertyItem::maxIntRole,420);

    QObjectImporter importer;
    QLabel *l=new QLabel();
    l->setObjectName("Whaou c'est les proprietes d'un QLabel");
    se=model->add(new PropertySectionItem("Tests d'import de QOBJECTS"));
    importer.importFrom(l,se);
    QTextBrowser *te=new QTextBrowser();
	te->setObjectName("Pourquoi pas un textbrowser ??");
	importer.importFrom(te,se);
    QTreeView widget;
    widget.setModel(model);
    //widget.setColumnCount(2);
    widget.setItemDelegate(new PropertyDelegate());
    widget.show();
    return app.exec();
}

////////////////////////////:

Vector3::Vector3()
        :m_x(0.0), m_y(0.0), m_z(0.0)
{}

Vector3::Vector3(float x, float y, float z)
        :m_x(x), m_y(y), m_z(z)
{}

Vector3::Vector3(const Vector3 &v)
        :m_x(v.m_x), m_y(v.m_y), m_z(v.m_z)
{}


Vector3::~Vector3()
{}

float Vector3::getX() const
{
    return m_x;
}

float Vector3::getY() const
{
    return m_y;
}

float Vector3::getZ() const
{
    return m_z;
}

void Vector3::setX(float x)
{
    m_x = x;
}

void Vector3::setY(float y)
{
    m_y = y;
}

void Vector3::setZ(float z)
{
    m_z = z;
}

