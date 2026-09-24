#include "iObjectComponent.h"

#include "../head/result_message_out.h"
bool IObjectComponent::removeChild( IObjectComponent *remove_target ) {
	auto count = children.size( );
	if( count ) {
		auto data = children.data( );
		decltype(count) index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ] == remove_target ) {
				children.erase( children.begin( ) + index );
				break;
			}
	}
	return true;
}
bool IObjectComponent::appendChild( IObjectComponent *append_target ) {
	auto count = children.size( );
	if( count ) {
		auto data = children.data( );
		decltype(count) index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ] == append_target )
				return true;
	}
	children.emplace_back( append_target );
	return true;
}
bool IObjectComponent::deleteChild( IObjectComponent *delete_target ) {
	bool result = delete_target->deleteThis( );
	if( result )
		return result;
	return Result_Var_Function_Messag_Ptr_Out_Args( result, this, deleteChild, QObject::tr( "释放异常 :[ %1 ] %2" ).arg( classTypeTools::getTypeName(delete_target ) ).arg( MessageString() <<delete_target ) );
}
bool IObjectComponent::deleteThis( ) {
	if( this == nullptr )
		return false;
	auto deleteTargetPtr = classTypeTools::cast_type< IObjectComponent >( this );
	if( deleteTargetPtr == nullptr )
		return false;
	if( deleteTargetPtr->parent )
		deleteTargetPtr->parent->removeChild( deleteTargetPtr );
	delete deleteTargetPtr;
	return true;
}
IObjectComponent::IObjectComponent( ) {
	regClassTypeInfoRef( this );
}

bool IObjectComponent::setParent( IObjectComponent *parent ) {
	bool appendChild = parent->appendChild( this );
	if( appendChild == false )
		return false;
	if( this->parent->removeChild( this ) == false )
		return false;
	this->parent = parent;
	return true;
}
IObjectComponent * IObjectComponent::getParent( ) const {
	return nullptr;
}
const std::vector< IObjectComponent * > & IObjectComponent::getChiildren( ) const {
	return children;
}
bool IObjectComponent::clearChiildren( ) {
	children.clear( );
	return true;
}
IObjectComponent::operator QObject *( ) {
	return toObject( );
}
IObjectComponent::~IObjectComponent( ) {
	auto count = children.size( );
	if( count ) {
		auto clone = children;
		clearChiildren( );
		auto data = clone.data( );
		decltype(count) index = 0;
		for( ; index < count; index += 1 )
			deleteChild( data[ index ] );
	}
}
