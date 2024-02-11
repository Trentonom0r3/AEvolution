#include "AEnums.h"


template void boost::serialization::serialize<boost::archive::text_oarchive, CommandID>(boost::archive::text_oarchive&, CommandID&, const unsigned int);
template void boost::serialization::serialize<boost::archive::text_iarchive, CommandID>(boost::archive::text_iarchive&, CommandID&, const unsigned int);

template void boost::serialization::serialize<boost::archive::text_oarchive, AEGP_CollectionItemType>(boost::archive::text_oarchive&, AEGP_CollectionItemType&, const unsigned int);
template void boost::serialization::serialize<boost::archive::text_iarchive, AEGP_CollectionItemType>(boost::archive::text_iarchive&, AEGP_CollectionItemType&, const unsigned int);

