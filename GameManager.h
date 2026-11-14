#if !defined(GAMEMANAGER_H)
#define GAMEMANAGER_H

typedef enum{
    Ingame,
    Start,
    End,
}GameState;

typedef enum{
    localmp,
    sp,
    srvc,
}GameMode;

#endif // GAMEMANAGER_H