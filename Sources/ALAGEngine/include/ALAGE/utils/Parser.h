#ifndef PARSER_H
#define PARSER_H

#include "ALAGE/utils/Singleton.h"

class Parser : public Singleton<Parser>
{
    public:
        friend class Singleton<Parser>;

        static bool IsBool(const std::string&);
        static bool IsInt(const std::string&);
        static bool IsFloat(const std::string&);

        static bool  ParseBool(const std::string&);
        static int   ParseInt(const std::string&);
        static float ParseFloat(const std::string&);

        static std::string FindFileDirectory(const std::string&);

    protected:
        Parser();
        virtual ~Parser();

    private:
};

#endif // PARSER_H
