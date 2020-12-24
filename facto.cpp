#include <inttypes.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include "gmp/gmp.h"

int main( int argc, const char* argv[] ) {
	uint64_t upTo = argc > 1 ? strtol( argv[1], nullptr, 10 ) : 0;
	if( !upTo ) upTo = 1000000;
	printf( "calculating factorial: %lu!\n", upTo );

	mpz_t accu[64];
	for( int i = 0; i < 64; i ++ ) mpz_init_set_ui( accu[i], 1 );

	for( uint64_t op1 = 2; op1 <= upTo; op1 ++ ) {
		mpz_mul_ui( accu[0], accu[0], op1 );
		for( int i = 0; i < 32; i++ ) {
			if( mpz_size( accu[i] ) > (64lu << (i<<0)) ) {
				mpz_mul( accu[i+1], accu[i+1], accu[i] );
				mpz_set_ui( accu[i], 1 );
			}
			else {
				break;
			}
		}
	}

	for( int i = 1; i < 64; i++ ) mpz_mul( accu[0], accu[0], accu[i] );

	printf( "   ...done. bigint value length is %zu digits in hex base.\n", mpz_sizeinbase( accu[0], 16 ) );
	printf( "unrolling decimal...\n" );

	if( char* dec = mpz_get_str( nullptr, 10, accu[0] ) ) {
		const char* idx = dec;
		uint64_t dgCount = 0;
		while( *idx ) {
			dgCount += *idx - '0';
			idx++;
		}
		printf( "   ...done. bigint value length is %zu digits in dec base.\n", idx - dec );
		printf( "result: %ld\n", dgCount );
		free( dec );
	}
	else {
		printf( "   ...oops, mpz_get_str failed.\n" );
	}

	for( int i = 0; i < 64; i ++ ) mpz_clear( accu[i] );
	return 0;
}
