#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Base64.h"

/* ×ª»»Ëã×Ó */
static char find_pos( char ch ) {
    char *ptr = ( char* )strrchr( base, ch );//the last position (the only) in base[] 
    return ( ptr - base );
}

IBase64 * base64_encode( IBase64 i_b )  {
    int prepare = 0,ret_len = 0,temp = 0,tmp = 0;
    char *ret = NULL;
    char *f = NULL;
    char changed[4];
    ret_len = i_b.size / 3;
    temp = i_b.size % 3;
    if( temp > 0 ) {
        ret_len += 1;
    }
    ret_len = ret_len * 4 + 1;
    ret = ( char * )malloc( ret_len );

    if( ret == NULL ) {
        printf( "No enough memory.\n" );
        exit( 0 );
    }
    memset( ret, 0, ret_len );
    f = ret;
    while( tmp < i_b.size ) {
        temp = 0;
        prepare = 0;
        memset( changed, '\0', 4 );
        while( temp < 3 ) {
            if( tmp >= i_b.size ) {
                break;
            }
            prepare = ( ( prepare << 8 ) | ( i_b.data[tmp] & 0xFF ) );
            tmp++;
            temp++;
        }
        prepare = ( prepare << ( ( 3 - temp ) * 8 ) );
        for(int i = 0; i < 4; i++ ) {
            if( temp < i ) {
                changed[i] = 0x40;
            } else {
                changed[i] = ( prepare >> ( ( 3 - i ) * 6 ) ) & 0x3F;
            }
            *f = base[changed[i]];
            f++;
        }
    }
    *f = '\0';
    IBase64 * rt = ( IBase64 * )malloc( sizeof( IBase64 ) );
    rt->data = ret;
    rt->size = ret_len - 1;

    return rt;
}

IBase64 * base64_decode( IBase64 i_b ) {
    int ret_len = ( i_b.size / 4 ) * 3;
    int size = ret_len, equal_count = 0,tmp = 0,temp = 0,prepare = 0;
    char *ret = NULL;
    char *f = NULL;
    if( *( i_b.data + i_b.size - 1 ) == '=' ) {
        equal_count += 1;
    }
    if( *( i_b.data + i_b.size - 2 ) == '=' ) {
        equal_count += 1;
    }
    if( *( i_b.data + i_b.size - 3 ) == '=' ) {//seems impossible 
        equal_count += 1;
    }
    switch( equal_count ) {
    case 0:
        ret_len += 4;//3 + 1 [1 for NULL] 
        break;
    case 1:
        ret_len += 4;//Ceil((6*3)/8)+1 
        break;
    case 2:
        ret_len += 3;//Ceil((6*2)/8)+1 
        break;
    case 3:
        ret_len += 2;//Ceil((6*1)/8)+1 
        break;
    }
    ret = ( char * )malloc( ret_len );
    if( ret == NULL ) {
        printf( "No enough memory.\n" );
        exit( 0 );
    }
    memset( ret, 0, ret_len );
    f = ret;
    while( tmp < ( i_b.size - equal_count ) ) {
        temp = 0;
        prepare = 0;
        while( temp < 4 ) {
            if( tmp >= ( i_b.size - equal_count ) ) {
                break;
            }
            prepare = ( prepare << 6 ) | ( find_pos( i_b.data[tmp] ) );
            temp++;
            tmp++;
        }
        prepare = prepare << ( ( 4 - temp ) * 6 );
        for(int i = 0; i<3; i++ ) {
            if( i == temp ) {
                break;
            }
            *f = ( char )( ( prepare >> ( ( 2 - i ) * 8 ) ) & 0xFF );
            f++;
        }
    }
    *f = '\0';
    IBase64 * rt = ( IBase64* )malloc( sizeof( IBase64 ) );
    rt->data = ret;
    rt->size = size - equal_count;
    return rt;
}