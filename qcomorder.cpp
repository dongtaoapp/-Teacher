#include "qcomorder.h"

QComOrder::QComOrder()
{

}

void QComOrder::GetTeachModeOrder(int nMode,QByteArray& data)
{
    data.clear();
    if(nMode == 0)
    {
        data.resize(13);
        data[0] = data[1] = data[2] = 0xCC;
        data[3] = 0xBF;
        data[4] = data[5] = 0x00;
        data[6] = 0x54;
        data[7] = data[8] = 0x00;
        data[9] = 0xBF;
        data[10] = 0x00;
        data[11] = 0x45;
        data[12] = 0x5A;
    }
    else if(nMode == 1)
    {

          data.resize(13);
          data[0] = 0xCC;
          data[1] = 0xCC;
          data[2] = 0xCC;
          data[3] = 0xBB;
          data[4] = 0xAA;
          data[5] = 0xAA;
          data[6] = 0x54;
          data[7] = data[8] = 0xAA;
          data[9] = 0xBB;
          data[10] = 0x00;
          data[11] = 0x45;
          data[12] = 0x5A;

    }
    else if(nMode == 2)
    {
        data.resize(13);
        data[0] = data[1] = data[2] = 0xCC;
        data[3] = 0xCE;
        data[4] = data[5] = 0x00;
        data[6] = 0x54;
        data[7] = data[8] = 0x00;
        data[9] = 0xCE;
        data[10] = 0x00;
        data[11] = 0x45;
        data[12] = 0x5A;
    }

}

void QComOrder::GetVidrPosOrder(BYTE pos, QByteArray &data)
{
    data.clear();
    data.resize(15);
    data[0] = data[1] = data[2] = 0xCC;
    data[3] = 0xCA;
    data[4] = 0xAA;
    data[5] = 0xAA;
    data[6] = 0x54;
    data[7] = 0xAA;
    data[8] = 0xAA;
    data[9] = 0xCA;
    data[10] = 1;
    data[11] = pos;
    data[14] = '\0';
    data[13] = 0x5A;
    data[12] = 0x45;
}

void QComOrder::GetStopVidrOrder(QByteArray &data)
{
    data.clear();
    data.resize(16);
    data[0] = data[1] = data[2] = 0xCC;
    data[3] = 0xCA;
    data[4] = 0xAA;
    data[5] = 0xAA;
    data[6] = 0x54;
    data[7] = 0xAA;
    data[8] = 0xAA;
    data[9] = 0xCA;
    data[10] = 2;
    data[11] = 0x00;
    data[12] = 0x00;
    data[13] = 0x45;
    data[14] = 0x5A;
    data[15] = '\0';
}

void QComOrder::ParseComReadData(QByteArray &data,QList<comDataStruct*>& lstdata)
{
    comDataStruct* pDataStruct = NULL;
    while( (pDataStruct = GetDataSturctFromData(data)) != NULL)
    {
        JugdeDataType(pDataStruct);
        lstdata.append(pDataStruct);
    }
}

void QComOrder::GetPalpateOrder(QByteArray &data, int nOrderNo)
{
    BYTE TXData[9];
    for( int n = 0; n < 9; ++n )
    {
        TXData[n] = 0;
    }
    switch( nOrderNo )
    {
    case 0:       //¸Îµ¨Æ¢Î´´¥¼°
        TXData[0]=0x0E;
        TXData[1]=0x01;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 1:      //¸Î´ó1ÀåÃ×£¬ÖÊÈí
        TXData[0]=0x0A;
        TXData[1]=0x02;
        TXData[2]=0x01;
        TXData[3]=0xCC;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 2:      //¸Î´ó3ÀåÃ×£¬ÖÊÈÍ
        TXData[0]=0x0A;
        TXData[1]=0x03;
        TXData[2]=0x03;
        TXData[3]=0xDD;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 3:      //¸Î´ó7ÀåÃ×£¬ÖÊÓ²
        TXData[0]=0x0A;
        TXData[1]=0x04;
        TXData[2]=0x07;
        TXData[3]=0xEE;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 4:       //µ¨ÄÒ´¥Í´
        TXData[0]=0x0B;
        TXData[1]=0x0F;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x03;
        TXData[6]=0x55;
        TXData[7]=0x02;
        break;
    case 5:       //Ä«·ÆÊÏÕ÷ÑôÐÔ
        TXData[0]=0x0B;
        TXData[1]=0x0E;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x02;
        TXData[6]=0x55;
        TXData[7]=0x01;
        break;
    case 6:       //µ¨ÄÒ´ó´¥Í´²»Ã÷ÏÔ
        TXData[0]=0x0B;
        TXData[1]=0x0D;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x01;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 7:      //Æ¢´ó2ÀåÃ×
        TXData[0]=0x0C;
        TXData[1]=0x05;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x02;
        TXData[5]=0x55;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 8:       //Æ¢´ó5ÀåÃ×
        TXData[0]=0x0C;
        TXData[1]=0x06;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x05;
        TXData[5]=0x55;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 9:       //Æ¢´ó7ÀåÃ×
        TXData[0]=0x0C;
        TXData[1]=0x07;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x07;
        TXData[5]=0x55;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 10:       //¸Î´ó1ÀåÃ×ÖÊÈíÆ¢´ó2ÀåÃ×
        TXData[0]=0x0E;
        TXData[1]=0x08;
        TXData[2]=0x01;
        TXData[3]=0xCC;
        TXData[4]=0x02;
        TXData[5]=0x55;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 11:         //¸Î´ó2ÀåÃ×ÖÊÈíÄ«·ÆÊÏÕ÷ÑôÐÔ
        TXData[0]=0x0E;
        TXData[1]=0x10;
        TXData[2]=0x02;
        TXData[3]=0xCC;
        TXData[4]=0x55;
        TXData[5]=0x02;
        TXData[6]=0x55;
        TXData[7]=0x01;
        break;
    case 12:         //¸Î´ó2ÀåÃ×ÖÊÈíÄ«·ÆÊÏÕ÷ÑôÐÔÆ¢´ó2ÀåÃ×
        TXData[0]=0x0E;
        TXData[1]=0x11;
        TXData[2]=0x02;
        TXData[3]=0xCC;
        TXData[4]=0x02;
        TXData[5]=0x02;
        TXData[6]=0x55;
        TXData[7]=0x01;
        break;
    case 13:       //¸ÎÖ×´ó3ÀåÃ×ÖÊµØÖÐµÈ¡¢Æ¢Ö×´ó2ÀåÃ×
        TXData[0]=0x0E;
        TXData[1]=0x09;
        TXData[2]=0x03;
        TXData[3]=0xDD;
        TXData[4]=0x02;
        TXData[5]=0x55;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 14:      //¸Î´ó3ÀåÃ×ÖÊÈÍÆ¢´ó1ÀåÃ×
        TXData[0]=0x0E;
        TXData[1]=0x0A;
        TXData[2]=0x03;
        TXData[3]=0xDD;
        TXData[4]=0x01;
        TXData[5]=0x55;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 15:       //¸Î´ó3ÀåÃ×ÖÊÈÍÆ¢´ó3ÀåÃ×
        TXData[0]=0x0E;
        TXData[1]=0x0B;
        TXData[2]=0x03;
        TXData[3]=0xDD;
        TXData[4]=0x03;
        TXData[5]=0x55;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 16:       //¸Î´ó7ÀåÃ×ÖÊÓ²Æ¢´ó5ÀåÃ×
        TXData[0]=0x0E;
        TXData[1]=0x0C;
        TXData[2]=0x07;
        TXData[3]=0xEE;
        TXData[4]=0x05;
        TXData[5]=0x55;
        TXData[6]=0x55;
        TXData[7]=0x55;
        break;
    case 17:        //Î¸À£ÑñÑ¹Í´
        TXData[0]=0x0D;
        TXData[1]=0x12;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x01;
        TXData[7]=0x04;
        break;
    case 18:        //Ê®¶þÖ¸³¦À£ÑñÑ¹Í´
        TXData[0]=0x0D;
        TXData[1]=0x13;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x03;
        TXData[7]=0x06;
        break;
    case 19:        //ÒÈÏÙÑ×Ñ¹Í´
        TXData[0]=0x0D;
        TXData[1]=0x14;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x05;
        TXData[7]=0x08;
        break;
    case 20:        //ÒÈÏÙÑ×·´ÌøÍ´
        TXData[0]=0x0D;
        TXData[1]=0x15;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x06;
        TXData[7]=0x09;
        break;
    case 21:        //À»Î²Ñ×Ñ¹Í´
        TXData[0]=0x0D;
        TXData[1]=0x16;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x07;
        TXData[7]=0x0A;
        break;
    case 22:        //À»Î²Ñ×·´ÌøÍ´
        TXData[0]=0x0D;
        TXData[1]=0x17;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x08;
        TXData[7]=0x0B;
        break;
    case 23:       //¸¹²¿Ñ¹Í´
        TXData[0]=0x0D;
        TXData[1]=0x18;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x09;
        TXData[7]=0x0C;
        break;
    case 24:      //¸¹²¿·´ÌøÍ´
        TXData[0]=0x0D;
        TXData[1]=0x19;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x0A;
        TXData[7]=0x0D;
        break;
    case 25:        //ÒÒ×´½á³¦Ñ¹Í´
        TXData[0]=0x0D;
        TXData[1]=0x1A;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x0D;
        TXData[7]=0x0F;
        break;
    case 26:        //Òì³£°ü¿é
        TXData[0]=0x0D;
        TXData[1]=0x1B;
        TXData[2]=0x55;
        TXData[3]=0x55;
        TXData[4]=0x55;
        TXData[5]=0x55;
        TXData[6]=0x0E;
        TXData[7]=0x12;
        break;
    default: //ÖÃÎ»(±àºÅÊÇ0x27Ò²ÊÇÕâ¸öÖµ)
        TXData[0]=0x0D;
        TXData[1]=0x1B;
        TXData[2]=0x0C;
        TXData[3]=0x0C;
        TXData[4]=0x0C;
        TXData[5]=0x0C;
        TXData[6]=0x0C;
        TXData[7]=0x0C;
    }
    TXData[8]= (TXData[0] + TXData[1] + TXData[2] + TXData[3] + TXData[4] + TXData[5] + TXData[6] + TXData[7])%256;

    data.clear();
    data.resize(22);
    data[0] = 0xCC;
    data[1] = 0xCC;
    data[2] = 0xCC;
    data[3] = TXData[1];
    data[4] = 0xAA;
    data[5] = 0xAA;
    data[6] = 'C';
    data[7] = 0xAA;
    data[8] = 0xAA;
    data[9] = 0xBD;
    data[10] = 9;
    for( int n = 0; n < 9; n++ )
    {
//		lptrArray->SetAt( 11 + n, TXData[n] );
        data[11+n] = TXData[n];
    }
    data[20] = 0x45;
    data[21] = 0x5a;

}

void QComOrder::GetAuscultateLinkOrder(QByteArray &data)
{
    data.clear();
    data.resize(13);
    data[0] = data[1] = data[2] = 0xCC;
    data[3] = 0x06;
    data[4] =0xAA; data[5] = 0x00;
    data[6] = 0x54;
    data[7] =0xAA; data[8] = 0x00;
    data[9] = 0x06;
    data[10] = 0x00;
    data[11] = 0x45;
    data[12] = 0x5A;
}

int QComOrder::ParseLinkOrder(const QByteArray &data)
{
    if(data.size() == 13)
    {
        if((((BYTE)data[4]) == 0x00))
            return 0;
        else
            return 1;
    }

    return -1;
}

void QComOrder::GetPalpateLinkOrder(QByteArray &data)
{
    data.clear();
    data.resize(13);
    data[0] = data[1] = data[2] = 0xCC;
    data[3] = 0x08;
    data[4] =0xAA; data[5] = 0xAA;
    data[6] = 0x43;
    data[7] =0xAA; data[8] = 0xAA;
    data[9] = 0x08;
    data[10] = 0x00;
    data[11] = 0x45;
    data[12] = 0x5A;
}

comDataStruct *QComOrder::GetDataSturctFromData(QByteArray &data)
{
 search:
    if(SearchBeginFlag(data))
    {
        int nLen = SearchEndFlag(data);
        if(nLen != -1 && nLen != -2)
        {
            comDataStruct* pDataStruct = new comDataStruct;
            pDataStruct->m_data = data.left(nLen);
            data = data.mid(nLen);
            return pDataStruct;
        }
        else if(nLen != -2)
        {
            data = data.mid(5);
            goto search;
        }

    }

    return NULL;
}

bool QComOrder::SearchBeginFlag(QByteArray &data)
{
    bool bFind = FALSE;
        while(data.size() >= 13)
        {
            QByteArray byteTemp = data.left(5);
            if( (((BYTE)byteTemp[0]) == 0xCC) && (((BYTE)byteTemp[1]) == 0xCC) && (((BYTE)byteTemp[2]) == 0xCC))
            {
                 bFind = TRUE;
                 break;
            }
            else
            {
                data = data.mid(1);
            }
        }
        return bFind;
}

int QComOrder::SearchEndFlag(const QByteArray &data)
{
    int nLen = -2;
    if(data[11] == 0x45 && data[12] == 0x5A)
    {
        nLen = 13;
    }
    else if(data.size() >= (data[9]+12))
    {
        nLen = data[9]+12;

        if( nLen <= 40 )
        {
            if( !(data[nLen-1] == 0x5A && data[nLen-2] == 0x45) )
                return -1;
        }
        else
            return -1;

    }
    return nLen;
}

void QComOrder::JugdeDataType(comDataStruct *pData)
{
    pData->m_byMainAddress = pData->m_data[3];
    pData->m_byMinorAddress = pData->m_data[4];
    if( ((BYTE)pData->m_data[5]) == 0x54)
        pData->m_bAuscultate = TRUE;
    else
        pData->m_bAuscultate = FALSE;
    switch (pData->m_data[8]) {
    case 0x52:
        pData->m_bAuscultate ? pData->m_nCmdType = 0 : pData->m_nCmdType = 1;
        break;
    case 0x51:
        pData->m_nCmdType = 2;
        break;
    }
}
