#include "polarssl/ssl.h"
#include "polarssl/ctr_drbg.h"

const char *opt_psk = "c033f52671c61c8128f7f8a40be88038bcf2b07a6eb3095c36e3759f0cf40837";
const char *opt_psk_identity = "psk_identity";

unsigned char psk[256];
size_t psk_len = 0;

ssl_context ssl;

void psk_unhexify() {
    unsigned char c;
    size_t j;

    if( strlen( opt_psk ) % 2 != 0 )
    {
        Serial.println("pre-shared key not valid hex\n");
        return;
    }

    psk_len = strlen( opt_psk ) / 2;

    for( j = 0; j < strlen( opt_psk ); j += 2 )
    {
        c = opt_psk[j];
        if( c >= '0' && c <= '9' )
            c -= '0';
        else if( c >= 'a' && c <= 'f' )
            c -= 'a' - 10;
        else if( c >= 'A' && c <= 'F' )
            c -= 'A' - 10;
        else
        {
            Serial.println("pre-shared key not valid hex\n");
            return;
        }
        psk[ j / 2 ] = c << 4;

        c = opt_psk[j + 1];
        if( c >= '0' && c <= '9' )
            c -= '0';
        else if( c >= 'a' && c <= 'f' )
            c -= 'a' - 10;
        else if( c >= 'A' && c <= 'F' )
            c -= 'A' - 10;
        else
        {
            Serial.println("pre-shared key not valid hex\n");
            return;
        }
        psk[ j / 2 ] |= c;
    }
}

/*char *hex_convert(int n, char *s)
{
	const char *hh = "0123456789ABCDEF";
	s[0] = hh[(n&0xF0)>>4];
	s[1] = hh[n&0x0F];
	s[2] = 0;
}
*/

static void my_debug(void *ctx, int level, const char *str)
{
	Serial.println(str);
}

int ar_recv(void *ctx, unsigned char *buf, size_t len)
{
	Serial.println("recv");
	for (int i=0; i<len; i++) {
		Serial.println(buf[i]);
	}
	return len;
}

int ar_send(void *ctx, const unsigned char *buf, size_t len)
{
	Serial.println("send");
	for (int i=0; i<len; i++) {
		Serial.println(buf[i]);
	}
	return len;
}

int ar_random(void *p_rng, unsigned char *output, size_t output_len)
{
	Serial.println("random");
	// This is probably really really bad
	return 0;
}

void setup()
{
	Serial.begin(9600);
	Serial.println("setup");

	Serial.println("unhexify");

	psk_unhexify();

	Serial.println("ssl_init");

	ssl_init(&ssl);

	Serial.println("ssl_set_rng");

	ssl_set_rng(&ssl, ar_random, 0);

	Serial.println("ssl_set_dbg");

	ssl_set_dbg(&ssl, my_debug, 0);

	Serial.println("ssl_set_bio");

	ssl_set_bio(&ssl, ar_recv, 0, ar_send, 0);

	Serial.println("ssl_set_psk");

	ssl_set_psk(&ssl, psk, psk_len, (const unsigned char *)opt_psk_identity, strlen(opt_psk_identity));

	Serial.println("ssl_handshake");

	int hs_res = ssl_handshake(&ssl);

	Serial.print("ssl_handshake = ");
	Serial.println(hs_res);
}

void loop()
{
	Serial.println("loop");
	delay(1000);
}
