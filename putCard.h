#if !defined __CMK2015WIN_PUTCARD__
#define __CMK2015WIN_PUTCARD__

class CPutChara;
class CCardList;
class CSuuji;
class CMyMessage;

class CPutCard
{
public:
	CPutCard(CMyMessage* message,CCardList* cardList);
	~CPutCard();
	void End(void);

	void PutCard(int x,int y,int card,int ps = 100);
	void PutMiniCard(POINT pt,int card,int ps = 100,int number = -1);
	void PutMiniCard(int x,int y,int card,int ps = 100,int number = -1);
protected:
	CCardList* m_cardList;

	int m_cardPicNumber;
	CPicture* m_cardPic;

	CMyMessage* m_message;

private:
	int m_seatMax;
	CPutChara* m_card[16];
	CPutChara* m_miniCard;
	CSuuji* m_minicardSuuji;
	CSuuji* m_etcSuuji;

	CPutChara* m_rare;
	CPutChara* m_type;
	CPutChara* m_cardMana;

	CPicture* m_cardBase[4];
	int m_rarePrintX;
	int m_rarePrintY;
	int m_namePrintX;
	int m_namePrintY;
	int m_textPrintX;
	int m_textPrintY;
	int m_textNextY;
	int m_typePrintX;
	int m_typePrintY;
	int m_cardManaPrintX;
	int m_cardmanaPrintY;
	int m_cardManaNextX;
	int m_etcPrintX;
	int m_etcPrintY;
	int m_etcNextX;

};

#endif
/*_*/
