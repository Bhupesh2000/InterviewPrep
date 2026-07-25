#ifndef USER_H
#define USER_H

#include "../enum/UserTier.h"

class User
{
    int id;
    UserTier tier;

public:
    User(int id, UserTier tier) : id(id), tier(tier){};
    ~User() = default;
    
    int getUserId(){
        return id;
    }

    UserTier getUserTier(){
        return tier;
    }
};

#endif