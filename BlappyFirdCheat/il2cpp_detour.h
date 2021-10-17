#pragma once
#include "defs.h"

namespace il2cpp_detour
{
	bool hook( MethodInfo* method, void** orig, void* hook )
    {
        if ( !method )
            return false;

        *orig = static_cast< void* >( method->methodPointer );

        DetourTransactionBegin( );
        DetourUpdateThread( GetCurrentThread( ) );
        DetourAttach( orig, hook );
        DetourTransactionCommit( );

        //printf( "hooked: %s\n", method->name );

        return true;
    };

    bool unhook( void** orig, void* hook )
    {
        DetourTransactionBegin( );
        DetourUpdateThread( GetCurrentThread( ) );
        DetourDetach( orig, hook );
        DetourTransactionCommit( );

        return true;
    };
}