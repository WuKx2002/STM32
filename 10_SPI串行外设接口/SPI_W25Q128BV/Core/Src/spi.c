/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    spi.c
 * @brief   This file provides code for the configuration
 *          of the SPI instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PB3     ------> SPI1_SCK
    PB4     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PB3     ------> SPI1_SCK
    PB4     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
 * �ӻ��ͺţ�W25Q128
 * ���Ŷ��壺/CS��PB14��SCK��PB3��MISO��PB4��MOSI��PB5
 *
 */
void W25Q128_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  SPI_HandleTypeDef hspi1;

  // 1.��SPI1��GPIOA����ʱ��
  __HAL_RCC_SPI1_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  // 2.����SPI���GPIO����PB3��PB4��PB5��/CS����PB14(/CS�͵�ƽ��Ч)
  GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;   // ���ű��
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                       // �����������
  GPIO_InitStruct.Pull = GPIO_NOPULL;                           // ��������
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;                    // ����ģʽSPI1
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);          // ����CS(PB14)
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // 3.����SPI�������
  hspi1.Instance = SPI1;                        // hspi1ʵ��ΪSPI1
  hspi1.Init.Mode = SPI_MODE_MASTER;            // ����ģʽ                
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;  // ˫��ȫ˫��
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;      // ����λ8bit
  hspi1.Init.CLKPolarity =  SPI_POLARITY_HIGH;  // ģʽ3ʱ�Ӽ��Ը�
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;        // ģʽ3�ڶ������زɼ�����
  hspi1.Init.NSS = SPI_NSS_SOFT;                // �������NSS
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;   // 2��ƵAPB2
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;                   // W25Q128��λ�ȳ�
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE; 
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
}

// ͨʱSPI���跢��һ���ֽ�����ͬʱ���յ�һ���ֽ�
uint8_t W25Q128_SendByte(uint8_t byte)
{
  while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_TXE ) == RESET);
  WRITE_REG(hspi1.Instance->DR, byte);
  while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_RXNE) == RESET);
  return READ_REG(hspi1.Instance->DR);
}

uint16_t W25Q128_ReadDeviceID(void)
{
  uint16_t ID = 0;

  // 1. ����CSƬѡ����
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

  // 2. ����ָ��0x90
  W25Q128_SendByte(0x90);

  // 3. ���͵�ַ 24bit
  W25Q128_SendByte(0x00);
  W25Q128_SendByte(0x00);
  W25Q128_SendByte(0x00);

  // 4. ���ճ���ID���豸ID, ���������������ݼ���
  ID = W25Q128_SendByte(0x00) << 8;   // ���ճ���ID�����ư�λȻ������豸ID
  ID |= W25Q128_SendByte(0x00);       // �����豸ID

  // 5. ����CS��ʾ����ͨ��
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

  return ID;
}

// дʹ��
void W25Q128_WriteEnable(void)
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
  W25Q128_SendByte(0x60);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
}

// дʧ��
void W25Q128_WriteDisable(void)
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
  W25Q128_SendByte(0x04);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
}

uint8_t W25Q128_ReadStatusRegister1(void)
{
  uint8_t status;

  // 1. ����CSƬѡ����
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

  // 2. ����ָ��
  W25Q128_SendByte(0x05);

  // 3. ���������ֽ����ݣ�Ŀ���ǽ���һ���ֽڵķ���ֵ
  status = W25Q128_SendByte(0x00);

  // 4. ����CS��ʾ����ͨ��
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

  return status;
}

void W25Q128_SectorErase(uint32_t Address)
{
  // 1. ����дʹ��
  W25Q128_WriteEnable();

  // 2. ����CSƬѡ����
  HAL_Delay(1);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

  // 3. ���Ͳ���ָ��20h
  W25Q128_SendByte(0x20);

  // 4. ���͵�ַ
  // ����Flash���������ԣ����֮ǰ�����Ѿ����������Ļ��������ڲ�����Ĭ����0xFF
  W25Q128_SendByte((Address & 0xFF0000) >> 16);
  W25Q128_SendByte((Address & 0xFF000) >> 8);
  W25Q128_SendByte((Address) & 0xFF);

  // 4. ����CS��ʾ����ͨ��
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
  
  // 6. �ȴ��������
  while (W25Q128_ReadStatusRegister1() & 0x01);

  // 7. �ر�дʹ��
  W25Q128_WriteDisable();

}

void W25Q128_ReadData(uint32_t Address, uint8_t *RecvBuf, uint32_t ReadLen)
{
  // 1. ����CSƬѡ����
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

  // 2. ����ָ��
  W25Q128_SendByte(0x03);

  // 3. ���͵�ַ
  W25Q128_SendByte((Address & 0xFF0000) >> 16);
  W25Q128_SendByte((Address & 0xFF000) >> 8);
  W25Q128_SendByte((Address) & 0xFF);

  // 4. ��������
  while (ReadLen--)
  {
    *RecvBuf++ = W25Q128_SendByte(0x00);
  }

  // 5. ����CS��ʾ����ͨ��
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

}

void W25Q128_PageProgram(uint32_t Address, uint8_t *RecvBuf, uint32_t ReadLen)
{
  // 1. ����дʹ��
  W25Q128_WriteEnable();

  // 2. ����CSƬѡ����
  HAL_Delay(1);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

  // 3. ���Ͳ���ָ��02h
  W25Q128_SendByte(0x02);

  // 4. ���͵�ַ
  // ����Flash���������ԣ����֮ǰ�����Ѿ����������Ļ��������ڲ�����Ĭ����0xFF
  W25Q128_SendByte((Address & 0xFF0000) >> 16);
  W25Q128_SendByte((Address & 0xFF000) >> 8);
  W25Q128_SendByte((Address) & 0xFF);

  // 5. ��������
  while (ReadLen--)
  {
    W25Q128_SendByte(*RecvBuf++);
  }

  // 6. ����CS��ʾ����ͨ��
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

  // 7. �ȴ�д�����
  while (W25Q128_ReadStatusRegister1() & 0x01);

  // 8. �ر�дʹ��
  W25Q128_WriteDisable();

}
/* USER CODE END 1 */
