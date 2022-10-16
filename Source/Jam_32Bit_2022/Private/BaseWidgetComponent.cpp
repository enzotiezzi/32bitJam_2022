// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidgetComponent.h"

UBaseWidgetComponent::UBaseWidgetComponent() 
{

}

UWidgetAnimation* UBaseWidgetComponent::GetAnimation(FText AnimationName)
{
    UProperty* Prop =this->GetWidget()->GetClass()->PropertyLink;

    while (Prop)
    {
        if (Prop->GetClass() == UObjectProperty::StaticClass())
        {
            UObjectProperty* ObjectProp = Cast<UObjectProperty>(Prop);

            if (ObjectProp->PropertyClass == UWidgetAnimation::StaticClass())
            {
                UObject* Object = ObjectProp->GetObjectPropertyValue_InContainer(this);

                UWidgetAnimation* WidgetAnim = Cast<UWidgetAnimation>(Object);

                if (WidgetAnim)
                {
                    if (WidgetAnim->GetFName().ToString().Contains(AnimationName.ToString()))
                        return WidgetAnim;
                }
            }
        }

        Prop = Prop->PropertyLinkNext;
    }

    return nullptr;
}