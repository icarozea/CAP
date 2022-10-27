#include "stencil.h"
#include <immintrin.h>


void ApplyStencil(unsigned char *img_in, unsigned char *img_out, int width, int height) {
	
	__m512i ss0, ss1, ss2, ss3, ss4, ss5, ss6, ss7, ss8, ssVal; 
	
	for (int i = 1; i < height-1; i++)
		for (int j = 1; j < width-1; j+=64) {

			ss0 = _mm512_loadu_si512((__m512i const*)&img_in[(i  )*width + j]);
			ss1 = _mm512_loadu_si512((__m512i const*)&img_in[(i-1)*width + j-1] );
			ss2 = _mm512_loadu_si512((__m512i const*)&img_in[(i-1)*width + j]);
			ss3 = _mm512_loadu_si512((__m512i const*)&img_in[(i-1)*width + j+1]);
			ss4 = _mm512_loadu_si512((__m512i const*)&img_in[(i  )*width + j-1] );
			ss5 = _mm512_loadu_si512((__m512i const*)&img_in[(i  )*width + j+1] );
			ss6 = _mm512_loadu_si512((__m512i const*)&img_in[(i+1)*width + j-1] );
			ss7 = _mm512_loadu_si512((__m512i const*)&img_in[(i+1)*width + j] );
			ss8 = _mm512_loadu_si512((__m512i const*)&img_in[(i+1)*width + j+1]);
			
			ssVal = ss0;
			ssVal = _mm512_sub_epi64(ssVal, ss1);
			ssVal = _mm512_add_epi64(ssVal, ss0);
			ssVal = _mm512_sub_epi64(ssVal, ss2);
			ssVal = _mm512_add_epi64(ssVal, ss0);
			ssVal = _mm512_sub_epi64(ssVal, ss3);
			ssVal = _mm512_add_epi64(ssVal, ss0);
			ssVal = _mm512_sub_epi64(ssVal, ss4);
			ssVal = _mm512_add_epi64(ssVal, ss0);
			ssVal = _mm512_sub_epi64(ssVal, ss5);
			ssVal = _mm512_add_epi64(ssVal, ss0);
			ssVal = _mm512_sub_epi64(ssVal, ss6);
			ssVal = _mm512_add_epi64(ssVal, ss0);
			ssVal = _mm512_sub_epi64(ssVal, ss7);
			ssVal = _mm512_add_epi64(ssVal, ss0);
			ssVal = _mm512_sub_epi64(ssVal, ss8);
			ssVal = _mm512_add_epi64(ssVal, ss0);

			_mm512_storeu_si512((__m512i *)&img_out[i*width + j], ssVal);
		}
}

void CopyImage(unsigned char *img_in, unsigned char *img_out, int width, int height) {

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			img_in[i*width + j] = img_out[i*width + j];
}
