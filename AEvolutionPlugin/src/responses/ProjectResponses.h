#pragma once
#include "../MessageMain.h"

class GetNumProjectsResp : public Response {
public:
	A_long num_projL;
	GetNumProjectsResp() = default;
	GetNumProjectsResp(A_long num_projL, std::string error) : num_projL(num_projL), Response(CommandID::GetNumProjects, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& num_projL;
	}
};

class GetProjectByIndexResp : public Response {
public:
    AE_Project project;
	GetProjectByIndexResp() = default;
	GetProjectByIndexResp(AEGP_ProjectH projectH, std::string error) : project(AE_Project(projectH)), Response(CommandID::GetProjectByIndex, error) {};
   
    template<class Archive>
    inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& project;
    }
};

class GetProjectNameResp : public Response {
public:
	std::string name;
	GetProjectNameResp() = default;
	GetProjectNameResp(std::string name, std::string error) : name(name), Response(CommandID::GetProjectName, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& name;
	}
};

class GetProjectPathResp : public Response {
public:
	std::string path;
	GetProjectPathResp() = default;
	GetProjectPathResp(std::string path, std::string error) : path(path), Response(CommandID::GetProjectPath, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& path;
	}
};

class GetProjectRootFolderResp : public Response {
public:
	AE_Item root_folder;
	GetProjectRootFolderResp() = default;
	GetProjectRootFolderResp(AEGP_ItemH root_folderH, std::string error) : root_folder(AE_Item(root_folderH)), Response(CommandID::GetProjectRootFolder, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& root_folder;
	}
};

class SaveProjectToPathResp : public Response {
public:
	SaveProjectToPathResp() = default;
	SaveProjectToPathResp(std::string error) : Response(CommandID::SaveProjectToPath, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetProjectTimeDisplayResp : public Response {
public:
	AEGP_TimeDisplay3 time_display;
	GetProjectTimeDisplayResp() = default;
	GetProjectTimeDisplayResp(AEGP_TimeDisplay3 time_display, std::string error) : time_display(time_display), Response(CommandID::GetProjectTimeDisplay, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& time_display;
	}
};

class SetProjectTimeDisplayResp : public Response {
public:
	SetProjectTimeDisplayResp() = default;
	SetProjectTimeDisplayResp(std::string error) : Response(CommandID::SetProjectTimeDisplay, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class ProjectIsDirtyResp : public Response {
public:
	A_Boolean is_dirtyB;
	ProjectIsDirtyResp() = default;
	ProjectIsDirtyResp(A_Boolean is_dirtyB, std::string error) : is_dirtyB(is_dirtyB), Response(CommandID::ProjectIsDirty, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& is_dirtyB;
	}
};

class SaveProjectAsResp : public Response {
public:
	SaveProjectAsResp() = default;
	SaveProjectAsResp(std::string error) : Response(CommandID::SaveProjectAs, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class NewProjectResp : public Response {
public:
	AE_Project new_project;
	NewProjectResp() = default;
	NewProjectResp(AEGP_ProjectH new_projectH, std::string error) : new_project(AE_Project(new_projectH)), Response(CommandID::NewProject, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& new_project;
	}
};

class OpenProjectFromPathResp : public Response {
public:
	AE_Project project;
	OpenProjectFromPathResp() = default;
	OpenProjectFromPathResp(AEGP_ProjectH projectH, std::string error) : project(AE_Project(projectH)), Response(CommandID::OpenProjectFromPath, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& project;
	}
};

class GetProjectBitDepthResp : public Response {
public:
	AEGP_ProjBitDepth bit_depth;
	GetProjectBitDepthResp() = default;
	GetProjectBitDepthResp(AEGP_ProjBitDepth bit_depth, std::string error) : bit_depth(bit_depth), Response(CommandID::GetProjectBitDepth, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& bit_depth;
	}
};

class SetProjectBitDepthResp : public Response {
public:
	SetProjectBitDepthResp() = default;
	SetProjectBitDepthResp(std::string error) : Response(CommandID::SetProjectBitDepth, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};



