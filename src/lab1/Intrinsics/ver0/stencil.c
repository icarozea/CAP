#include "stencil.h"
#include <immintrin.h>

void ApplyStencilIntrinsic(unsigned char *img_in, unsigned char *img_out, int width, int height) {
  
	short val;
	unsigned char val_out;

	__m256i ss0, ss1, ss2, ss3, ss4, ss5, ss6, ss7, ss8, ssVal; 

	for (int i = 1; i < height-1; i++)
		for (int j = 1; j < width-1; j+=8) {

			ss0 = _mm256_loadu_si256((__m256i const*)&img_in[(i  )*width + j]);
			ss1 = _mm256_loadu_si256((__m256i const*)&img_in[(i-1)*width + j-1] );
			ss2 = _mm256_loadu_si256((__m256i const*)&img_in[(i-1)*width + j]);
			ss3 = _mm256_loadu_si256((__m256i const*)&img_in[(i-1)*width + j+1]);
			ss4 = _mm256_loadu_si256((__m256i const*)&img_in[(i  )*width + j-1] );
			ss5 = _mm256_loadu_si256((__m256i const*)&img_in[(i  )*width + j+1] );
			ss6 = _mm256_loadu_si256((__m256i const*)&img_in[(i+1)*width + j-1] );
			ss7 = _mm256_loadu_si256((__m256i const*)&img_in[(i+1)*width + j] );
			ss8 = _mm256_loadu_si256((__m256i const*)&img_in[(i+1)*width + j+1]);
			
			ssVal = ss0;
			ssVal = _mm256_subs_epi8(ssVal, ss1);
			ssVal = _mm256_adds_epi8(ssVal, ss0);
			ssVal = _mm256_subs_epi8(ssVal, ss2);
			ssVal = _mm256_adds_epi8(ssVal, ss0);
			ssVal = _mm256_subs_epi8(ssVal, ss3);
			ssVal = _mm256_adds_epi8(ssVal, ss0);
			ssVal = _mm256_subs_epi8(ssVal, ss4);
			ssVal = _mm256_adds_epi8(ssVal, ss0);
			ssVal = _mm256_subs_epi8(ssVal, ss5);
			ssVal = _mm256_adds_epi8(ssVal, ss0);
			ssVal = _mm256_subs_epi8(ssVal, ss6);
			ssVal = _mm256_adds_epi8(ssVal, ss0);
			ssVal = _mm256_subs_epi8(ssVal, ss7);
			ssVal = _mm256_adds_epi8(ssVal, ss0);
			ssVal = _mm256_subs_epi8(ssVal, ss8);
			ssVal = _mm256_adds_epi8(ssVal, ss0);

			_mm256_storeu_si256((__m256i *)&img_out[i*width + j], ssVal);
		}
}


void ApplyStencil(unsigned char *img_in, unsigned char *img_out, int width, int height) {
  
	short val;
	unsigned char val_out;

	for (int i = 1; i < height-1; i++)
		for (int j = 1; j < width-1; j++) {
			val = img_in[(i  )*width + j];
			val +=	-img_in[(i-1)*width + j-1] -   img_in[(i-1)*width + j] - img_in[(i-1)*width + j+1] 
					-img_in[(i  )*width + j-1] + 7*img_in[(i  )*width + j] - img_in[(i  )*width + j+1] 
					-img_in[(i+1)*width + j-1] -   img_in[(i+1)*width + j] - img_in[(i+1)*width + j+1];
			if (val<0){
				val=0;
			}else val_out = (unsigned char)val;
			if (val>255){
				val_out=255;
			}else val_out = (unsigned char)val;

			img_out[i*width + j] = (unsigned char)(val_out);
		}
}

void CopyImage(unsigned char *img_in, unsigned char *img_out, int width, int height) {

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			img_in[i*width + j] = img_out[i*width + j];
}
