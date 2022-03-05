HAL_StatusTypeDef DAC_Init( void );
HAL_StatusTypeDef DAC_Start( void );
HAL_StatusTypeDef DAC_DMA_Start( uint32_t * const dacBuf, uint32_t const Length );
uint32_t DAC_GetSamplingFrequency(void);
