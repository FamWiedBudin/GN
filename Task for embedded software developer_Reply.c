/*
Task for embedded software developer
- You need to make a queue for sending integers from one process to another.
- You can assume both processes have access to the same memory
- You need to take multiprocessing into account as one process might be running in interrupt context or the processes might be running on different CPUs
- You are allowed to limit the number of elements in the queue
- You are allowed to add any initialization functions.
- Implementation should be done in C.
Thus, you will have to implement the following functions:
*/
#define GN_AUDIO_BUF_SIZE 256
#define true 1
#define false 0
void InitGnAudioBuf(void);
bool GnAudioPut(uint32_t val);
bool GnAudioGet(uint32_t *val);

uint32_t Param[GN_AUDIO_BUF_SIZE];
uint8_t Read_inx;
uint8_t Write_inx;
uint8_t Buf_cnt;
uint8_t Semafor;
void InitGnAudioBuf(void)
{
  Read_inx = 0;
  Write_Inx = 0;
  Semafor = 0;
  Buf_cnt = 0;
}
/** Put one value in the queue.
 *
 *  @param[in] val the value to be put in the queue
 *
 *  @return True if the value got into the queue, false otherwise.
 */

bool GnAudioPut(uint32_t val)
{
   while(Semafor);
  Semafor = 1;
  if(Buf_cnt == GN_AUDIO_BUF_SIZE)
    return false;
  
  Param[Write_inx++] = val;
  if(Write_inx >= GN_AUDIO_BUF_SIZE)
  Write_inx = 0;
  Buf_cnt++;
  Semafor = 0;
  return true;
}
/** Get one value from the queue and remove it from the queue.
 *
 *  @param[out] *val the value from the queue if any
 *
 *  @return True if a value was in the queue, false otherwise.
 */
bool GnAudioGet(uint32_t *val)
{
   while(Semafor);
  Semafor = 1;
  if(!Buf_cnt)
    return false;
  *val = Param[Read_inx++];
  if(Read_inx >= GN_AUDIO_BUF_SIZE)
    Read_inx = 0;
  Buf_cnt--;
  Semafor = 0;
  return true;
}

