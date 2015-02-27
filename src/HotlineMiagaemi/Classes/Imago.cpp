#include "Imago.h"


Imago::Imago()
:m_Satiety(70)
{
    m_IsFeed = true;
    m_IsBrainwash = true;
    m_IsTrain = true;
    m_IsInfiltrate = true;
    m_IsStatVisible = true;

	m_Type = IMAGO;
}


Imago::~Imago()
{
}
