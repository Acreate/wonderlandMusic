#include "iWidgetComponent.h"
IWidgetComponent::IWidgetComponent( ) {
	regClassTypeInfoRef( this );
}
IWidgetComponent::operator QWidget *( ) {
	return toWidget( );
}
