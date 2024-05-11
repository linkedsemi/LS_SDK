#include "stdint.h"
#include "adpcm.h"

#define CLIP(data, min, max) \
if ((data) > (max)) data = max; \
else if ((data) < (min)) data = min;


/* Quantizer step size lookup table */
static const uint16_t StepSizeTable[89]={7,8,9,10,11,12,13,14,16,17,
                            19,21,23,25,28,31,34,37,41,45,
                            50,55,60,66,73,80,88,97,107,118,
                            130,143,157,173,190,209,230,253,279,307,
                            337,371,408,449,494,544,598,658,724,796,
                            876,963,1060,1166,1282,1411,1552,1707,1878,2066,
                            2272,2499,2749,3024,3327,3660,4026,4428,4871,5358,
                            5894,6484,7132,7845,8630,9493,10442,11487,12635,13899,
                            15289,16818,18500,20350,22385,24623,27086,29794,32767};
/* Table of index changes */
static const int8_t IndexTable[16]={0xff,0xff,0xff,0xff,2,4,6,8,0xff,0xff,0xff,0xff,2,4,6,8};
/* Intel ADPCM step variation table */
// static const int8_t IndexTable[16]={-1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8};
static const int index_table[] = {/* adpcm data size is 4 */-1, -1, -1, -1, 2, 4, 6, 8};   
/* Global ADPCM values for google TV remoter */
google_tv_audio_adpcm gAudioAdpcmVal; 

/**
  * @brief  ADPCM_Encode.
  * @param sample: a 16-bit PCM sample
  * @retval : a 4-bit ADPCM sample
  */
uint8_t ADPCM_Encode(int32_t sample)
{
  static int16_t  index = 0;
  static int32_t predsample = 0;
  uint8_t code=0;
  uint16_t tmpstep=0;
  int32_t diff=0;
  int32_t diffq=0;
  uint16_t step=0;
  
  step = StepSizeTable[index];

  /* 2. compute diff and record sign and absolut value */
  diff = sample-predsample;
  if (diff < 0)  
  {
    code=8;
    diff = -diff;
  }    
  
  /* 3. quantize the diff into ADPCM code */
  /* 4. inverse quantize the code into a predicted diff */
  tmpstep = step;
  diffq = (step >> 3);

  if (diff >= tmpstep)
  {
    code |= 0x04;
    diff -= tmpstep;
    diffq += step;
  }
  
  tmpstep = tmpstep >> 1;

  if (diff >= tmpstep)
  {
    code |= 0x02;
    diff -= tmpstep;
    diffq+=(step >> 1);
  }
  
  tmpstep = tmpstep >> 1;
  
  if (diff >= tmpstep)
  {
    code |=0x01;
    diffq+=(step >> 2);
  }
  
  /* 5. fixed predictor to get new predicted sample*/
  if (code & 8)
  {
    predsample -= diffq;
  }
  else
  {
    predsample += diffq;
  }  

  /* check for overflow*/
  if (predsample > 32767)
  {
    predsample = 32767;
  }
  else if (predsample < -32768)
  {
    predsample = -32768;
  }
  
  /* 6. find new stepsize index */
  index += IndexTable[code];
  /* check for overflow*/
  if (index <0)
  {
    index = 0;
  }
  else if (index > 88)
  {
    index = 88;
  }
  
  /* 8. return new ADPCM code*/
  return (code & 0x0f);
}



/**
  * @brief  ADPCM_Decode.
  * @param code: a byte containing a 4-bit ADPCM sample. 
  * @retval : 16-bit ADPCM sample
  */
int16_t ADPCM_Decode(uint8_t code)
{
  static int16_t  index = 0;
  static int32_t predsample = 0;
  uint16_t step=0;
  int32_t diffq=0;
  
  step = StepSizeTable[index];

  /* 2. inverse code into diff */
  diffq = step>> 3;
  if (code&4)
  {
    diffq += step;
  }
  
  if (code&2)
  {
    diffq += step>>1;
  }
  
  if (code&1)
  {
    diffq += step>>2;
  }

  /* 3. add diff to predicted sample*/
  if (code&8)
  {
    predsample -= diffq;
  }
  else
  {
    predsample += diffq;
  }
  
  /* check for overflow*/
  if (predsample > 32767)
  {
    predsample = 32767;
  }
  else if (predsample < -32768)
  {
    predsample = -32768;
  }

  /* 4. find new quantizer step size */
  index += IndexTable [code];
  /* check for overflow*/
  if (index < 0)
  {
    index = 0;
  }
  if (index > 88)
  {
    index = 88;
  }
  
  /* 5. save predict sample and index for next iteration */
  /* done! static variables */
  
  /* 6. return new speech sample*/
  return ((int16_t)predsample);
}

/* @brief Encode a frame of 15-bit PCM data to IMA-ADPCM (4-bit)
 *        4-bits ADPCMs are concated together to one byte using HighBits to judge
 * 
 */
void Adpcm_FrameEncode(const int16_t *PCMBuffer, void *EncodeBuffer, int32_t Len)
{
	int32_t i;
	uint8_t HighBits;
	uint8_t Code;
	uint8_t *pCode;
	
	HighBits = 0;
	pCode = (uint8_t *)EncodeBuffer;
	for (i=0; i<Len; i++) {
		Code = ADPCM_Encode(PCMBuffer[i]);
		if (HighBits) {
			*pCode |= Code << 4;
			pCode++;
			HighBits = 0;
		} else {
			*pCode = Code;
			HighBits = 1;
		}
	}
}



void Adpcm_FrameDecode(int16_t *PCMBuffer, const void *EncodeBuffer, int32_t Len)
{
	int32_t i;
	uint8_t HighBits;
	uint8_t Code;
	const uint8_t *pCode;
	
	HighBits = 0;
	pCode = (uint8_t *)EncodeBuffer;
	for (i=0; i<Len; i++) {
		if (HighBits) {
			Code = *pCode >> 4;
			pCode++;
			HighBits = 0;
		} else {
			Code = *pCode & 0xf;
			HighBits = 1;
		}
		PCMBuffer[i] = ADPCM_Decode(Code);
	}	
}

/* ---------------------------------------------------------------- */
/* Google TV remote audio format 
 *  Header (6 bytes) + Data (128 bytes)
 *  Header = 2 bytes audio frame number 
 *         + 1 byte  remote control id
 *         + 2 bytes previous predicted ADPCM value
 *         + 1 byte  Index into step table
 */

/**
  * @brief  ADPCM_Encode.
  * @param sample: a 16-bit PCM sample
  * @retval : a 4-bit ADPCM sample
  */
uint8_t ADPCM_Encode_Google_TV_Audio(int32_t sample)
{
  // static int16_t  index = 0;
  // static int32_t predsample = 0;
  int16_t index;
  int32_t predsample;

  uint8_t code=0;
  uint16_t tmpstep=0;
  int32_t diff=0;
  int32_t diffq=0;
  uint16_t step=0;
  
  index = gAudioAdpcmVal.tableIndex;
  predsample = gAudioAdpcmVal.previous_predict_adpcm;

  /*---------- original ADPCM -------------*/
  step = StepSizeTable[index];

  /* 2. compute diff and record sign and absolut value */
  diff = sample-predsample;
  if (diff < 0)  
  {
    code=8;
    diff = -diff;
  }    
  
  /* 3. quantize the diff into ADPCM code */
  /* 4. inverse quantize the code into a predicted diff */
  tmpstep = step;
  diffq = (step >> 3);

  if (diff >= tmpstep)
  {
    code |= 0x04;
    diff -= tmpstep;
    diffq += step;
  }
  
  tmpstep = tmpstep >> 1;

  if (diff >= tmpstep)
  {
    code |= 0x02;
    diff -= tmpstep;
    diffq+=(step >> 1);
  }
  
  tmpstep = tmpstep >> 1;
  
  if (diff >= tmpstep)
  {
    code |=0x01;
    diffq+=(step >> 2);
  }
  
  /* 5. fixed predictor to get new predicted sample*/
  if (code & 8)
  {
    predsample -= diffq;
  }
  else
  {
    predsample += diffq;
  }  

  /* check for overflow*/
  if (predsample > 32767)
  {
    predsample = 32767;
  }
  else if (predsample < -32768)
  {
    predsample = -32768;
  }
  
  /* 6. find new stepsize index */
  index += IndexTable[code];
  /* check for overflow*/
  if (index <0)
  {
    index = 0;
  }
  else if (index > 88)
  {
    index = 88;
  }
  
  /* 8. update global index and predict sample */
  gAudioAdpcmVal.tableIndex = index;
  gAudioAdpcmVal.previous_predict_adpcm = predsample ;  
  /* 9. return new ADPCM code*/

  return (code & 0x0f);
}

/* @brief Encode a frame of 15-bit PCM data to IMA-ADPCM (4-bit)
 *        4-bits ADPCMs are concated together to one byte using HighBits to judge
 * 
 */
void Adpcm_FrameEncode_Google_TV_Audio(const int16_t *PCMBuffer, void *EncodeBuffer, google_tv_audio_header *AudioHeader, int32_t Len)
{
	int32_t i;
	uint8_t HighBits;
	uint8_t Code;
	uint8_t *pCode;
	/* assign audio header */
  AudioHeader->frame_number++;
  AudioHeader->adpcmVal.previous_predict_adpcm = gAudioAdpcmVal.previous_predict_adpcm;
  AudioHeader->adpcmVal.tableIndex = gAudioAdpcmVal.tableIndex;
  /* calculate ADPCM */
	HighBits = 0;
	pCode = (uint8_t *)EncodeBuffer;
	for (i=0; i<Len; i++) {
		Code = ADPCM_Encode_Google_TV_Audio(PCMBuffer[i]);
		if (HighBits) {
			*pCode |= Code << 4;
			pCode++;
			HighBits = 0;
		} else {
			*pCode = Code;
			HighBits = 1;
		}
	}
}

void Adpcm_FrameEncode_Restart(google_tv_audio_header *AudioHeader)
{
	memset(&gAudioAdpcmVal, 0x0, sizeof(gAudioAdpcmVal));
  memset(AudioHeader, 0x0, sizeof(google_tv_audio_header));
}



/********************************* 4-bit ADPCM decoder ********************************/

/* Decode the block of ADPCM data into PCM. This requires no context because ADPCM blocks
 * are indeppendently decodable. This assumes that a single entire block is always decoded;
 * it must be called multiple times for multiple blocks and cannot resume in the middle of a
 * block.
 *
 * Parameters:
 *  outbuf          destination for interleaved PCM samples
 *  inbuf           source ADPCM block
 *  inbufsize       size of source ADPCM block
 *  channels        number of channels in block (must be determined from other context)
 *
 * Returns number of converted composite samples (total samples divided by number of channels)
 */ 

int Adpcm_Decode_Block(int16_t *outbuf, const uint8_t *inbuf, size_t inbufsize, int channels)
{
  int ch, samples = 1, chunks;
  int32_t pcmdata[2];
  int8_t index[2];

  if (inbufsize < channels * 4)
    return 0;

  for (ch = 0; ch < channels; ch++)
  {
    *outbuf++ = pcmdata[ch] = (int16_t)(inbuf[0] | (inbuf[1] << 8));
    index[ch] = inbuf[2];

    if (index[ch] < 0 || index[ch] > 88 || inbuf[3])
    {
      // printf("decode block error %d %d\n", index[ch], inbuf[3]);
      return 0;
    } // sanitize the input a little...

    inbufsize -= 4;
    inbuf += 4;
  }

  chunks = inbufsize / (channels * 4);
  samples += chunks * 8;

  while (chunks--)
  {
    int ch, i;

    for (ch = 0; ch < channels; ++ch)
    {

      for (i = 0; i < 4; ++i)
      {
        int step = StepSizeTable[index[ch]], delta = step >> 3;

        if (*inbuf & 1)
          delta += (step >> 2);
        if (*inbuf & 2)
          delta += (step >> 1);
        if (*inbuf & 4)
          delta += step;
        if (*inbuf & 8)
          delta = -delta;

        pcmdata[ch] += delta;
        index[ch] += index_table[*inbuf & 0x7];
        CLIP(index[ch], 0, 88);
        CLIP(pcmdata[ch], -32768, 32767);
        outbuf[i * 2 * channels] = pcmdata[ch];

        step = StepSizeTable[index[ch]], delta = step >> 3;

        if (*inbuf & 0x10)
          delta += (step >> 2);
        if (*inbuf & 0x20)
          delta += (step >> 1);
        if (*inbuf & 0x40)
          delta += step;
        if (*inbuf & 0x80)
          delta = -delta;

        pcmdata[ch] += delta;
        index[ch] += index_table[(*inbuf >> 4) & 0x7];
        CLIP(index[ch], 0, 88);
        CLIP(pcmdata[ch], -32768, 32767);
        outbuf[(i * 2 + 1) * channels] = pcmdata[ch];

        inbuf++;
      }

      outbuf++;
    }

    outbuf += channels * 7;
  }

  return samples;
}

