#ifndef _WIRE_H_
#define _WIRE_H_
 
#include "mbed.h"
 
#define TWI_DELAY(x)                    wait_us(x);
 
#define BUFF_MAX_LENGTH                 128
 
#define MAX_TIMEOUT_LOOPS               (20000UL)
 
#define TWI_FREQUENCY_100K              0 
#define TWI_FREQUENCY_250K              1 
#define TWI_FREQUENCY_400K              2 
 
#define TWI_SCL                         7
#define TWI_SDA                         30
 
 
class TwoWire
{  
    public :
        TwoWire(NRF_TWI_Type *twi_use);
        void begin();
        void begin(uint32_t scl_pin, uint32_t sda_pin, uint8_t speed);
        void beginTransmission(uint8_t);
        void beginTransmission(int);
        uint8_t endTransmission(void);
        uint8_t endTransmission(uint8_t);
        uint8_t requestFrom(uint8_t, uint8_t);
        uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
        uint8_t requestFrom(int, int);
        uint8_t requestFrom(int, int, int);
        int write(uint8_t);
        int write(const uint8_t *, size_t);
        int available(void);
        int read(void);  
        
     private : 
        uint8_t RX_Buffer[BUFF_MAX_LENGTH];
        uint8_t RX_BufferIndex;
        uint8_t RX_BufferLength;
        
        uint8_t TX_Buffer[BUFF_MAX_LENGTH];
        uint8_t TX_BufferIndex;
        uint8_t TX_BufferLength;
        
        NRF_TWI_Type *twi;
        
        uint8_t PPI_channel;
        uint8_t Transform_Addr;
        
        uint32_t SDA_Pin;
        uint32_t SCL_Pin;
        
        uint32_t twi_frequency;
 
        enum TwoWireStatus {
            UNINITIALIZED,
            MASTER_IDLE,
            MASTER_SEND,
            MASTER_RECV,
            SLAVE_IDLE,
            SLAVE_RECV,
            SLAVE_SEND
        };
        TwoWireStatus twi_status;
        
        bool twi_master_clear_bus(void);
        bool twi_master_init(void);
        uint8_t twi_master_read(uint8_t *data, uint8_t data_length, uint8_t issue_stop_condition);
        uint8_t twi_master_write(uint8_t *data, uint8_t data_length, uint8_t issue_stop_condition);
};
 
#endif