#pragma once
#include "GameServerMessage.h"
#include "MessageIdEnum.h"
#include "ContentsEnum.h"
#include "ContentsStructure.h"

class LoginMessage : public GameServerMessage                    
{                                                               
public:                                                         
	std::string ID;
	std::string PW;
                                                                
public:                                                         
    LoginMessage()                                               
        : GameServerMessage(static_cast<uint32_t>(MessageId::Login))                    
        , ID()
        , PW()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~LoginMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(ID) + DataSizeCheck(PW);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << ID;
        _Serializer << PW;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> ID;
        _Serializer >> PW;

    }                                                           
};                                                              

class CreateCharacterMessage : public GameServerMessage                    
{                                                               
public:                                                         
	std::string NickName;
                                                                
public:                                                         
    CreateCharacterMessage()                                               
        : GameServerMessage(static_cast<uint32_t>(MessageId::CreateCharacter))                    
        , NickName()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~CreateCharacterMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(NickName);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << NickName;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> NickName;

    }                                                           
};                                                              

class SelectCharacterMessage : public GameServerMessage                    
{                                                               
public:                                                         
	std::string NickName;
                                                                
public:                                                         
    SelectCharacterMessage()                                               
        : GameServerMessage(static_cast<uint32_t>(MessageId::SelectCharacter))                    
        , NickName()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~SelectCharacterMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(NickName);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << NickName;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> NickName;

    }                                                           
};                                                              

class ClientToReadyMessage : public GameServerMessage                    
{                                                               
public:                                                         
	uint64_t ObjectIndex;
	uint64_t ThreadIndex;
	uint64_t SectionIndex;
                                                                
public:                                                         
    ClientToReadyMessage()                                               
        : GameServerMessage(static_cast<uint32_t>(MessageId::ClientToReady))                    
        , ObjectIndex()
        , ThreadIndex()
        , SectionIndex()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~ClientToReadyMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(ObjectIndex) + DataSizeCheck(ThreadIndex) + DataSizeCheck(SectionIndex);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << ObjectIndex;
        _Serializer << ThreadIndex;
        _Serializer << SectionIndex;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> ObjectIndex;
        _Serializer >> ThreadIndex;
        _Serializer >> SectionIndex;

    }                                                           
};                                                              

class LevelMoveReplyMessage : public GameServerMessage                    
{                                                               
public:                                                         
	uint64_t ObjectIndex;
	uint64_t ThreadIndex;
	uint64_t SectionIndex;
                                                                
public:                                                         
    LevelMoveReplyMessage()                                               
        : GameServerMessage(static_cast<uint32_t>(MessageId::LevelMoveReply))                    
        , ObjectIndex()
        , ThreadIndex()
        , SectionIndex()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~LevelMoveReplyMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(ObjectIndex) + DataSizeCheck(ThreadIndex) + DataSizeCheck(SectionIndex);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << ObjectIndex;
        _Serializer << ThreadIndex;
        _Serializer << SectionIndex;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> ObjectIndex;
        _Serializer >> ThreadIndex;
        _Serializer >> SectionIndex;

    }                                                           
};                                                              

class RankRequestMessage : public GameServerMessage                    
{                                                               
public:                                                         
	std::string NickName;
                                                                
public:                                                         
    RankRequestMessage()                                               
        : GameServerMessage(static_cast<uint32_t>(MessageId::RankRequest))                    
        , NickName()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~RankRequestMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(NickName);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << NickName;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> NickName;

    }                                                           
};                                                              

class GetInventoryMessage : public GameServerMessage                    
{                                                               
public:                                                         
	int CharacterIndex;
                                                                
public:                                                         
    GetInventoryMessage()                                               
        : GameServerMessage(static_cast<uint32_t>(MessageId::GetInventory))                    
        , CharacterIndex()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~GetInventoryMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(CharacterIndex);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << CharacterIndex;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> CharacterIndex;

    }                                                           
};                                                              

class EquipItemMessage : public GameServerMessage                    
{                                                               
public:                                                         
	int CharacterIndex;
	int CurrentItemIndex;
	int ChangeItemIndex;
	int ItemPart;
                                                                
public:                                                         
    EquipItemMessage()                                               
        : GameServerMessage(static_cast<uint32_t>(MessageId::EquipItem))                    
        , CharacterIndex()
        , CurrentItemIndex()
        , ChangeItemIndex()
        , ItemPart()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~EquipItemMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(CharacterIndex) + DataSizeCheck(CurrentItemIndex) + DataSizeCheck(ChangeItemIndex) + DataSizeCheck(ItemPart);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << CharacterIndex;
        _Serializer << CurrentItemIndex;
        _Serializer << ChangeItemIndex;
        _Serializer << ItemPart;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> CharacterIndex;
        _Serializer >> CurrentItemIndex;
        _Serializer >> ChangeItemIndex;
        _Serializer >> ItemPart;

    }                                                           
};                                                              

class LogoutMessage : public GameServerMessage                    
{                                                               
public:                                                         
	std::string ID;
                                                                
public:                                                         
    LogoutMessage()                                               
        : GameServerMessage(static_cast<uint32_t>(MessageId::Logout))                    
        , ID()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~LogoutMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(ID);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << ID;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> ID;

    }                                                           
};                                                              

