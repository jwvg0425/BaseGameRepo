#include "Larva.h"


Larva::Larva()
:m_Satiety(0)
{
    m_IsFeed = true;
    m_IsBrainwash = true;
    m_IsTrain = false;
    m_IsInfiltrate = false;
    m_IsStatVisible = true;

	m_Type = LARVA;
}


Larva::~Larva()
{
}

Sprite* Larva::getSprite()
{
    return Sprite::create("larva_1.png");
}

bool Larva::isEvolve()
{
	return false;
}

Ant* Larva::evolve()
{
	//TODO : ��ȭ�ϸ� �� �Ǵ��� ���ؼ� ����(������ ��ü ����)

	return nullptr;
}

void Larva::update(float dTime)
{

}
