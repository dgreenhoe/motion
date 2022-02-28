void Tx_SetLow( int const n );
void Tx_SetHigh( int const n );
void Tx_Toggle( int const n );
int Tx_ReadState( int const n );
int Rx_ReadState( int const n );
void Tx_SetLowAll( void );
void Tx_SetHighAll( void );
int Tx_ReadStateAll( void );
int Rx_ReadStateAll( void );
int TxRx_Test( int const n, uint32_t const Duration );
int TxRx_TestAll( void );
void Tx_SetLevel( int const n, bool const Level );
int TxRx_GetNumChannels( void );
void Tx_ToggleAll( void );

