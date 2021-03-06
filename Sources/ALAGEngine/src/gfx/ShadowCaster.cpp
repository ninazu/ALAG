#include "ALAGE/gfx/GeometricShadowCaster.h"

namespace alag
{

ShadowCaster::ShadowCaster()
{
    m_shadowCastingType = NoShadow;
}

ShadowCaster::~ShadowCaster()
{
    while(!m_shadowDrawable.empty())
    {
        delete m_shadowDrawable.begin()->second;
        m_shadowDrawable.erase(m_shadowDrawable.begin());
    }
}


void ShadowCaster::RenderShadow(sf::RenderTarget* w/*, const sf::RenderStates &state*/, Light* light)
{
    std::map<Light*, sf::Drawable*>::iterator shadowIt;
    shadowIt = m_shadowDrawable.find(light);
    if(shadowIt != m_shadowDrawable.end())
        w->draw(*shadowIt->second/*, state*/);
}


sf::IntRect ShadowCaster::GetShadowMaxShift(Light* light)
{
    std::map<Light*, sf::IntRect>::iterator shadowIt;
    shadowIt = m_shadowMaxShift.find(light);
    if(shadowIt == m_shadowMaxShift.end())
        return sf::IntRect(0,0,0,0);
    else
        return shadowIt->second;
}


void ShadowCaster::AskForDynamicShadowUpdate()
{
    std::map<Light*, bool>::iterator lightIt;
    for(lightIt = m_requireShadowCasting.begin() ;
        lightIt !=  m_requireShadowCasting.end() ; ++lightIt)
        {
            if(lightIt->first->GetType() == OmniLight)
                lightIt->second = true;
        }
}

void ShadowCaster::AskForAllShadowUpdate()
{
    std::map<Light*, bool>::iterator lightIt;
    for(lightIt = m_requireShadowCasting.begin() ;
        lightIt !=  m_requireShadowCasting.end() ; ++lightIt)
            lightIt->second = true;
}

ShadowCastingType ShadowCaster::GetShadowCastingType()
{
    return m_shadowCastingType;
}

bool ShadowCaster::IsRequiringShadowCasting(Light* light)
{
    std::map<Light*, bool>::iterator shadowIt;
    shadowIt = m_requireShadowCasting.find(light);
    if(shadowIt == m_requireShadowCasting.end())
        return true;
    else
        return shadowIt->second;
}

void ShadowCaster::AddToLightList(Light* light)
{
     m_requireShadowCasting[light] = false;
}

void ShadowCaster::ForceShadowCastingType(ShadowCastingType type)
{
    m_shadowCastingType = type;
}


void ShadowCaster::Notify(NotificationSender* sender, NotificationType type)
{
    /*std::map<Light*, bool>::iterator lightIt;
    lightIt = m_requireShadowCasting.find((Light*)sender);
    if(lightIt != m_requireShadowCasting.end()
    && type == Notification_LightMoved)
        lightIt->second = true;*/

    if(sender == (NotificationSender*)m_parentNode)
    {
        if(type == Notification_SceneNodeMoved)
            AskForDynamicShadowUpdate();
    }

    SceneObject::Notify(sender, type);
}

}
