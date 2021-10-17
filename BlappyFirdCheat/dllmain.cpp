#include "defs.h"

il2cpp_callable_t< UnityEngine_Component_o* ( * )( UnityEngine_Component_o*, System_Type_o* ) > component_get_component;
il2cpp_callable_t< Il2CppObject* ( * )( UnityEngine_Transform_o* ) > transform_get_position;
il2cpp_callable_t< void( * )( UnityEngine_Transform_o*, UnityEngine_Vector3_o* )> transform_set_position;
il2cpp_callable_t< Il2CppObject* ( * )( UnityEngine_Transform_o* ) > transform_get_rotation;
il2cpp_callable_t< void( * )( UnityEngine_Transform_o*, UnityEngine_Quaternion_o* )> transform_set_rotation;
il2cpp_callable_t< Il2CppObject* ( * )( void* ) > time_get_delta_time;
il2cpp_callable_t< Il2CppObject* ( * )( void*, float*, float*, float* ) > quaternion_euler;
il2cpp_callable_t< Il2CppObject* ( * )( void* ) > gui_utility_get_gui_depth;

bool fly = false;
bool no_clip = false;
bool spin = false;

void console_menu( )
{
    static bool init = true;

    const auto update_required = [ ] ( ) -> bool
    {
        if ( GetAsyncKeyState( VK_F1 ) & 1 )
        {
            fly = !fly;
            return true;
        }
        if ( GetAsyncKeyState( VK_F2 ) & 1 )
        {
            no_clip = !no_clip;
            return true;
        }
        if ( GetAsyncKeyState( VK_F3 ) & 1 )
        {
            spin = !spin;
            return true;
        }

        if ( init )
            return true;

        return false;
    }( );

    if ( !update_required )
        return;

    if ( init )
        init = false;

    system( "cls" );

    printf( fly ? "\033[1;32m" : "\033[1;31m" );
    printf( "F1 - Fly Mode [Control: W A S D]\n" );

    printf( no_clip ? "\033[1;32m" : "\033[1;31m" );
    printf( "F2 - No Clip\n" );

    printf( spin ? "\033[1;32m" : "\033[1;31m" );
    printf( "F3 - Spin Mode\n" );
}

void unload( );

void* orig_trigger_enter_2d = nullptr;
void hooked_trigger_enter_2d( PlayerController_o* thisptr, UnityEngine_Collider2D_o* collision )
{
    if ( no_clip )
        return;

    return static_cast< decltype( &hooked_trigger_enter_2d ) >( orig_trigger_enter_2d )( thisptr, collision );
}

void* orig_set_rotation = nullptr;
void hooked_set_rotation( UnityEngine_Transform_o* thisptr, UnityEngine_Quaternion_o* rotation )
{
    if ( spin && rotation->fields.x > -1000.f )
        return;

    if ( rotation->fields.x < -1000.f )
        rotation->fields.x += 1337.f;

    return static_cast< decltype( &hooked_set_rotation ) >( orig_set_rotation )( thisptr, rotation );
}

void* orig_fixed_update = nullptr;
void hooked_fixed_update( PlayerController_o* thisptr )
{
    console_menu( );

    if ( GetAsyncKeyState( VK_F7 ) )
        unload( );

    static float orig_gravity = 0.f;
    if ( orig_gravity == 0.f )
        orig_gravity = thisptr->fields.gravity;

    [ & ] ( ) -> void
    {
        const auto transform_type = il2cpp_helper::get_type( "UnityEngine", "Transform" );
        if ( bad_ptr( transform_type ) )
            return;

        const auto transform = reinterpret_cast< UnityEngine_Transform_o* >( component_get_component( reinterpret_cast< UnityEngine_Component_o* >( thisptr ), transform_type ) );
        if ( bad_ptr( transform ) )
            return;

        const auto delta_time = time_get_delta_time( )->unbox< float >( );
        if ( bad_ptr( delta_time ) )
            return;

        if ( spin )
        {
            const auto rotation = transform_get_rotation( transform )->unbox< UnityEngine_Quaternion_o >( );
            if ( bad_ptr( rotation ) )
                return;

            const auto euler = util::quaternion_to_euler( rotation );

            float roll = euler.fields.z * ( 180.f / M_PI );
            roll -= 600.f * *delta_time;

            const auto normalize_angle = [ ] ( float& angle ) -> void
            {
                if ( angle < 0.f )
                    angle += 360.f;
                else if ( angle > 360.f )
                    angle -= 360.f;
            };

            normalize_angle( roll );

            float null_float = 0.f;
            const auto new_rotation = quaternion_euler( nullptr, &null_float, &null_float, &roll )->unbox< UnityEngine_Quaternion_o >( );
            if ( bad_ptr( rotation ) )
                return;

            new_rotation->fields.x -= 1337.f;

            transform_set_rotation( transform, new_rotation );
        }

        if ( fly )
        {
            thisptr->fields.gravity = 0.f;
            thisptr->fields.velocity = 0.f;

            const auto position = transform_get_position( transform )->unbox< UnityEngine_Vector3_o >( );
            if ( bad_ptr( position ) )
                return;

            if ( GetAsyncKeyState( 'W' ) )
            {
                position->fields.y += 7.f * *delta_time;
                transform_set_position( transform, position );
            }
            if ( GetAsyncKeyState( 'S' ) )
            {
                position->fields.y += -7.f * *delta_time;
                transform_set_position( transform, position );
            }
            if ( GetAsyncKeyState( 'A' ) )
            {
                position->fields.x += -7.f * *delta_time;
                transform_set_position( transform, position );
            }
            if ( GetAsyncKeyState( 'D' ) )
            {
                position->fields.x += 7.f * *delta_time;
                transform_set_position( transform, position );
            }
            return;
        }
        else
            thisptr->fields.gravity = orig_gravity;
    }( );

    return static_cast< decltype( &hooked_fixed_update ) >( orig_fixed_update )( thisptr );
}

void* orig_set_text = nullptr;
void hooked_set_text( UnityEngine_UI_Text_o* thisptr, System_String_o* value )
{
    const auto text = reinterpret_cast< wchar_t* >( &value->fields.m_firstChar );

    if ( const auto score = _wtoi( text ) )
    {
        char new_text[ 100 ];
        sprintf_s( new_text, "-%i", score );
        value = il2cpp_helper::create_string( new_text );
    }

    return static_cast< decltype( &hooked_set_text ) >( orig_set_text )( thisptr, value );
}

HMODULE module;

void unload( )
{
    if ( orig_fixed_update )
        il2cpp_detour::unhook( &orig_fixed_update, hooked_fixed_update );
    if ( orig_trigger_enter_2d )
        il2cpp_detour::unhook( &orig_trigger_enter_2d, hooked_trigger_enter_2d );
    if ( orig_set_rotation )
        il2cpp_detour::unhook( &orig_set_rotation, hooked_set_rotation );
    if ( orig_set_text )
        il2cpp_detour::unhook( &orig_set_text, hooked_set_text );

    FreeLibraryAndExitThread( module, 0 );
}

void init( )
{
    AllocConsole( );
    FILE* fp = nullptr;
    freopen_s( &fp, "CONOUT$", "w", stdout );

    SetConsoleTitleW( L"BlappyFirdCheat" );

    il2cpp_helper::init( );

    il2cpp_detour::hook( il2cpp_helper::get_method_from_name( "", "PlayerController", "FixedUpdate", 0 ),
        &orig_fixed_update, hooked_fixed_update );
    il2cpp_detour::hook( il2cpp_helper::get_method_from_name( "", "PlayerController", "OnTriggerEnter2D", 1 ),
        &orig_trigger_enter_2d, hooked_trigger_enter_2d );
    il2cpp_detour::hook( il2cpp_helper::get_method_from_name( "UnityEngine", "Transform", "set_rotation", 1 ),
        &orig_set_rotation, hooked_set_rotation );
    il2cpp_detour::hook( il2cpp_helper::get_method_from_name( "UnityEngine.UI", "Text", "set_text", 1 ),
        &orig_set_text, hooked_set_text );

    component_get_component.initialize( "UnityEngine", "Component", "GetComponent" );
    transform_get_position.initialize( "UnityEngine", "Transform", "get_position" );
    transform_set_position.initialize( "UnityEngine", "Transform", "set_position" );
    transform_get_rotation.initialize( "UnityEngine", "Transform", "get_rotation" );
    transform_set_rotation.initialize( "UnityEngine", "Transform", "set_rotation" );
    time_get_delta_time.initialize( "UnityEngine", "Time", "get_deltaTime" );
    quaternion_euler.initialize( "UnityEngine", "Quaternion", "Euler" );
    gui_utility_get_gui_depth.initialize( "UnityEngine", "GUIUtility", "get_guiDepth" );
}

BOOL __stdcall DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
    if ( ul_reason_for_call == DLL_PROCESS_ATTACH )
    {
        module = hModule;
        init( );
    }
    return 1;
}