#pragma once
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>

class BaseH {
public:
    virtual ~BaseH() {}
    BaseH() {}
    BaseH(std::string sessionID) : sessionID(sessionID) {}
    std::string getSessionID() { return sessionID; }

protected:
    std::string sessionID;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& sessionID;
    }
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(BaseH)

class ItemH : public BaseH {
public:
    ItemH() {}
    ItemH(std::string sessionID) : BaseH(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<BaseH>(*this);
    }
};

class ProjectH : public BaseH {
public:
    ProjectH() {}
    ProjectH(std::string sessionID) : BaseH(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<BaseH>(*this);
    }
};

class CompH : public BaseH {
public:
    CompH() {}
    CompH(std::string sessionID) : BaseH(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<BaseH>(*this);
    }
};

class LayerH : public BaseH {
public:
    LayerH() {}
    LayerH(std::string sessionID) : BaseH(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<BaseH>(*this);
    }
};

class Collection2H : public BaseH {
public:
    Collection2H() {}
    Collection2H(std::string sessionID) : BaseH(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<BaseH>(*this);
    }
};

class CollectionItemH : public BaseH {
public:
    CollectionItemH() {}
    CollectionItemH(std::string sessionID) : BaseH(sessionID) {}
    std::string type = "";
    std::string typeSessionID = "";
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<BaseH>(*this);
        ar& type;
        ar& typeSessionID;
    }
};


class StreamRefH : public BaseH {
public:
    StreamRefH() {}
    StreamRefH(std::string sessionID) : BaseH(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<BaseH>(*this);
    }
};

class EffectRefH : public BaseH {
public:
    EffectRefH() {}
    EffectRefH(std::string sessionID) : BaseH(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<BaseH>(*this);
    }
};

class FootageH : public BaseH {
public:
    FootageH() {}
    FootageH(std::string sessionID) : BaseH(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<BaseH>(*this);
    }
};

struct dimensionsH {
    int width = 0;
    int height = 0;
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& width;
        ar& height;
    }
};

struct colorH {
    float r = 0;
    float g = 0;
    float b = 0;
    float a = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& r;
        ar& g;
        ar& b;
        ar& a;
    }
};
