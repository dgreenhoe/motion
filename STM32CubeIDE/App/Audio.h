int Audio_DMA_SawTooth( uint32_t const FundamentalFrequency );
int Audio_DMA_Triangle( uint32_t const FundamentalFrequency );
int Audio_DMA_Square(   uint32_t const FundamentalFrequency );
int Audio_DMA_Cosine(   uint32_t const FundamentalFrequency );
int Audio_Silence( void );
int Audio_Init(void);
int Audio_AudioData(void);
int Audio_DumpDACbuf( uint32_t const Start, uint32_t const NumSamples );
