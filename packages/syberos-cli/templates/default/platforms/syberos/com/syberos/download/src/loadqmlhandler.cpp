#include "loadqmlhandler.h"
#include "loadqmlwidget.h"

int LoadQmlHandler::typeId = qRegisterMetaType<LoadQmlHandler*>();
LoadQmlHandler::LoadQmlHandler(){

}
LoadQmlHandler::~LoadQmlHandler(){

}
void LoadQmlHandler::loadQml(QString parentPageName, QString parentName, QString type){
    LoadQmlWidget *widget = new LoadQmlWidget(parentPageName,parentName,type) ;
  if(widget){
      widget->showWidget();
  }

}
