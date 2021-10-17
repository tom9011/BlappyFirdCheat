#pragma once
#include "defs.h"

struct Il2CppDomain;
struct Il2CppAssembly;
struct Il2CppImage;
struct FieldInfo;
struct Il2CppThread;
struct Il2CppException;
struct Il2CppString;
struct Il2CppArray;

Il2CppDomain* ( *il2cpp_domain_get )( ) = nullptr;
Il2CppAssembly** ( *il2cpp_domain_get_assemblies )( Il2CppDomain*, size_t* ) = nullptr;
Il2CppImage* ( *il2cpp_assembly_get_image )( Il2CppAssembly* ) = nullptr;
Il2CppClass* ( *il2cpp_class_from_name )( const void*, const char*, const char* ) = nullptr;
Il2CppClass* ( *il2cpp_object_get_class )( Il2CppObject* ) = nullptr;
FieldInfo* ( *il2cpp_class_get_field_from_name )( Il2CppClass*, const char* ) = nullptr;
void( *il2cpp_field_static_get_value )( FieldInfo*, void* ) = nullptr;
void( *il2cpp_field_static_set_value )( FieldInfo*, void* ) = nullptr;
void( *il2cpp_field_get_value )( Il2CppObject*, FieldInfo*, void* ) = nullptr;
void( *il2cpp_field_set_value )( Il2CppObject*, FieldInfo*, void* ) = nullptr;
FieldInfo* ( *il2cpp_class_get_fields )( Il2CppClass*, void** ) = nullptr;
Il2CppType* ( *il2cpp_class_get_type ) ( Il2CppClass* ) = nullptr;
Il2CppObject* ( *il2cpp_type_get_object )( Il2CppType* ) = nullptr;
MethodInfo* ( *il2cpp_class_get_method_from_name )( Il2CppClass*, const char*, int ) = nullptr;
MethodInfo* ( *il2cpp_class_get_methods )( Il2CppClass*, void** ) = nullptr;
Il2CppThread* ( *il2cpp_thread_attach )( Il2CppDomain* ) = nullptr;
void( *il2cpp_thread_detach )( Il2CppThread* ) = nullptr;
Il2CppObject* ( *il2cpp_runtime_invoke )( MethodInfo*, void*, void**, Il2CppException** ) = nullptr;
Il2CppString* ( *il2cpp_string_new )( const char* ) = nullptr;
Il2CppString* ( *il2cpp_string_new_utf16 )( const wchar_t*, int32_t ) = nullptr;
Il2CppArray* ( *il2cpp_array_new )( Il2CppClass*, il2cpp_array_size_t ) = nullptr;
Il2CppObject* ( *il2cpp_object_new )( Il2CppClass* ) = nullptr;
void* ( *Il2CppObject::il2cpp_object_unbox )( Il2CppObject* ) = nullptr;
Il2CppObject* ( *il2cpp_value_box )( Il2CppClass*, void* ) = nullptr;
const char* ( *il2cpp_method_get_param_name )( MethodInfo*, uint32_t );
uint32_t( *il2cpp_method_get_param_count )( MethodInfo* );
Il2CppType* ( *il2cpp_method_get_param )( MethodInfo*, uint32_t );
const char* ( *il2cpp_type_get_name )( Il2CppType* );

System_RuntimeTypeHandle_o( *type_get_type_handle )( Il2CppObject* ) = nullptr;
System_Type_o* ( *type_get_type_from_handle )( System_RuntimeTypeHandle_o ) = nullptr;

MethodInfo* object_find_objects_of_type = nullptr;

namespace il2cpp_helper
{
	MethodInfo* get_method_from_name( const char*, const char*, const char*, int, bool( * )( MethodInfo* ) = nullptr );

	void init( )
	{
		auto game_assembly = GetModuleHandleA( "GameAssembly.dll" );
		if ( !game_assembly )
			return;
		
		il2cpp_domain_get = reinterpret_cast< decltype( il2cpp_domain_get ) >( GetProcAddress( game_assembly, "il2cpp_domain_get" ) );
		il2cpp_domain_get_assemblies = reinterpret_cast< decltype( il2cpp_domain_get_assemblies ) >( GetProcAddress( game_assembly, "il2cpp_domain_get_assemblies" ) );
		il2cpp_assembly_get_image = reinterpret_cast< decltype( il2cpp_assembly_get_image ) >( GetProcAddress( game_assembly, "il2cpp_assembly_get_image" ) );
		il2cpp_class_from_name = reinterpret_cast< decltype( il2cpp_class_from_name ) >( GetProcAddress( game_assembly, "il2cpp_class_from_name" ) );
		il2cpp_object_get_class = reinterpret_cast< decltype( il2cpp_object_get_class ) >( GetProcAddress( game_assembly, "il2cpp_object_get_class" ) );
		il2cpp_class_get_field_from_name = reinterpret_cast< decltype( il2cpp_class_get_field_from_name ) >( GetProcAddress( game_assembly, "il2cpp_class_get_field_from_name" ) );
		il2cpp_field_static_get_value = reinterpret_cast< decltype( il2cpp_field_static_get_value ) >( GetProcAddress( game_assembly, "il2cpp_field_static_get_value" ) );
		il2cpp_field_static_set_value = reinterpret_cast< decltype( il2cpp_field_static_set_value ) >( GetProcAddress( game_assembly, "il2cpp_field_static_set_value" ) );
		il2cpp_field_get_value = reinterpret_cast< decltype( il2cpp_field_get_value ) >( GetProcAddress( game_assembly, "il2cpp_field_get_value" ) );
		il2cpp_field_set_value = reinterpret_cast< decltype( il2cpp_field_set_value ) >( GetProcAddress( game_assembly, "il2cpp_field_set_value" ) );
		il2cpp_class_get_fields = reinterpret_cast< decltype( il2cpp_class_get_fields ) >( GetProcAddress( game_assembly, "il2cpp_class_get_fields" ) );
		il2cpp_class_get_type = reinterpret_cast< decltype( il2cpp_class_get_type ) >( GetProcAddress( game_assembly, "il2cpp_class_get_type" ) );
		il2cpp_type_get_object = reinterpret_cast< decltype( il2cpp_type_get_object ) >( GetProcAddress( game_assembly, "il2cpp_type_get_object" ) );
		il2cpp_class_get_method_from_name = reinterpret_cast< decltype( il2cpp_class_get_method_from_name ) >( GetProcAddress( game_assembly, "il2cpp_class_get_method_from_name" ) );
		il2cpp_class_get_methods = reinterpret_cast< decltype( il2cpp_class_get_methods ) >( GetProcAddress( game_assembly, "il2cpp_class_get_methods" ) );
		il2cpp_thread_attach = reinterpret_cast< decltype( il2cpp_thread_attach ) >( GetProcAddress( game_assembly, "il2cpp_thread_attach" ) );
		il2cpp_thread_detach = reinterpret_cast< decltype( il2cpp_thread_detach ) >( GetProcAddress( game_assembly, "il2cpp_thread_detach" ) );
		il2cpp_runtime_invoke = reinterpret_cast< decltype( il2cpp_runtime_invoke ) >( GetProcAddress( game_assembly, "il2cpp_runtime_invoke" ) );
		il2cpp_string_new = reinterpret_cast< decltype( il2cpp_string_new ) >( GetProcAddress( game_assembly, "il2cpp_string_new" ) );
		il2cpp_string_new_utf16 = reinterpret_cast< decltype( il2cpp_string_new_utf16 ) >( GetProcAddress( game_assembly, "il2cpp_string_new_utf16" ) );
		il2cpp_array_new = reinterpret_cast< decltype( il2cpp_array_new ) >( GetProcAddress( game_assembly, "il2cpp_array_new" ) );
		il2cpp_object_new = reinterpret_cast< decltype( il2cpp_object_new ) >( GetProcAddress( game_assembly, "il2cpp_object_new" ) );
		Il2CppObject::il2cpp_object_unbox = reinterpret_cast< decltype( Il2CppObject::il2cpp_object_unbox ) >( GetProcAddress( game_assembly, "il2cpp_object_unbox" ) );
		il2cpp_value_box = reinterpret_cast< decltype( il2cpp_value_box ) >( GetProcAddress( game_assembly, "il2cpp_value_box" ) );
		il2cpp_method_get_param_name = reinterpret_cast< decltype( il2cpp_method_get_param_name ) >( GetProcAddress( game_assembly, "il2cpp_method_get_param_name" ) );
		il2cpp_method_get_param_count = reinterpret_cast< decltype( il2cpp_method_get_param_count ) >( GetProcAddress( game_assembly, "il2cpp_method_get_param_count" ) );
		il2cpp_method_get_param = reinterpret_cast< decltype( il2cpp_method_get_param ) >( GetProcAddress( game_assembly, "il2cpp_method_get_param" ) );
		il2cpp_type_get_name = reinterpret_cast< decltype( il2cpp_type_get_name ) >( GetProcAddress( game_assembly, "il2cpp_type_get_name" ) );
		
		if ( auto type_get_type_handle_method = get_method_from_name( "System", "Type", "GetTypeHandle", 1 ) )
			type_get_type_handle = reinterpret_cast< decltype( type_get_type_handle ) >( type_get_type_handle_method->methodPointer );

		if ( auto type_get_type_from_handle_method = get_method_from_name( "System", "Type", "GetTypeFromHandle", 1 ) )
			type_get_type_from_handle = reinterpret_cast< decltype( type_get_type_from_handle ) >( type_get_type_from_handle_method->methodPointer );

		if ( auto object_find_objects_of_type_method = get_method_from_name( "UnityEngine", "Object", "FindObjectsOfType", 1 ) )
			object_find_objects_of_type = object_find_objects_of_type_method;
	}

	MethodInfo* get_method_from_name( const char* namespaze, const char* klass_name, const char* name, int param_count, bool( *filter_callback )( MethodInfo* ) )
	{
		const auto domain = il2cpp_domain_get( );
		if ( !domain )
			return nullptr;

		size_t assembly_list_size = 0;
		if ( const auto assembly_list = il2cpp_domain_get_assemblies( domain, &assembly_list_size ) )
		{
			for ( size_t i = 0; i < assembly_list_size; i++ )
			{
				const auto assembly = assembly_list[ i ];
				if ( !assembly )
					continue;

				const auto image = il2cpp_assembly_get_image( assembly );
				if ( !image )
					continue;

				const auto klass = il2cpp_class_from_name( image, namespaze, klass_name );
				if ( !klass )
					continue;

				void* iter = nullptr;
				MethodInfo* method;
				while ( method = il2cpp_class_get_methods( klass, &iter ) )
				{
					if ( method->parameters_count != param_count )
						continue;

					if ( name && strcmp( method->name, name ) )
						continue;

					if ( !filter_callback || filter_callback( method ) )
						return method;
				}
			}
		}

		return nullptr;
	}

	System_String_o* create_string( const char* str )
	{
		return reinterpret_cast< System_String_o* >( il2cpp_string_new( str ) );
	}

	System_Type_o* get_type( const char* namespaze, const char* name )
	{
		const auto domain = il2cpp_domain_get( );
		if ( !domain )
			return nullptr;

		size_t assembly_list_size = 0;
		if ( const auto assembly_list = il2cpp_domain_get_assemblies( domain, &assembly_list_size ) )
		{
			for ( size_t i = 0; i < assembly_list_size; i++ )
			{
				const auto assembly = assembly_list[ i ];
				if ( !assembly )
					continue;

				const auto image = il2cpp_assembly_get_image( assembly );
				if ( !image )
					continue;

				const auto klass = il2cpp_class_from_name( image, namespaze, name );
				if ( !klass )
					continue;

				const auto object = il2cpp_object_new( klass );
				if ( !object )
					continue;

				return type_get_type_from_handle( type_get_type_handle( object ) );
			}
		}

		return nullptr;
	}

	__declspec( noinline ) UnityEngine_Object_array* find_objects_by_name( const char* namespaze, const char* name )
	{
		const auto system_type = get_type( namespaze, name );
		if ( !system_type )
			return nullptr;

		const auto domain = il2cpp_domain_get( );
		if ( !domain )
			return nullptr;

		void* params[] = { system_type };
		Il2CppException* exc = nullptr;
		Il2CppObject* result = nullptr;

		[ & ]( ) -> void
		{
			__try
			{
				result = il2cpp_runtime_invoke( object_find_objects_of_type, nullptr, params, &exc );
			}
			__except ( EXCEPTION_EXECUTE_HANDLER )
			{
			}
		}( );

		return reinterpret_cast< UnityEngine_Object_array* >( result );
	}
}

template < typename >
struct il2cpp_callable_t;

template < typename Object, typename Ret, typename... Args >
struct il2cpp_callable_t< Ret( * )( Object, Args... ) >
{
private:
	MethodInfo* method_info;

public:
	void initialize( const char* namespaze, const char* klass_name, const char* name, bool( *filter_callback )( MethodInfo* ) = nullptr )
	{
		this->method_info = il2cpp_helper::get_method_from_name( namespaze, klass_name, name, sizeof...( Args ), filter_callback );

		if ( !this->method_info )
			printf( "error: method %s.%s::%s (%i) not found.\n", namespaze, klass_name, name, sizeof...( Args ) );
	}

	Ret operator( )( Object obj = nullptr, Args... args )
	{
		void** params = nullptr;

		if constexpr ( sizeof...( args ) > 0 )
		{
			std::vector< void* > vec = { args... };
			params = new void* [ sizeof...( args ) ];

			memcpy( params, &vec[ 0 ], sizeof...( args ) * sizeof( void* ) );
		}

		Il2CppException* exc = nullptr;
		Il2CppObject* result = nullptr;

		[ & ]( ) -> void
		{
			__try
			{
				result = il2cpp_runtime_invoke( this->method_info, obj, params, &exc );
			}
			__except ( EXCEPTION_EXECUTE_HANDLER )
			{
				printf( "%s almost crashed!\n", this->method_info->name );
			}
		}( );

		if ( params )
			delete[] params;

		if constexpr ( !std::is_same<Ret, void>::value )
			return ( Ret ) result;
	}
};