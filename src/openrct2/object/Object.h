/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "../common.h"
#include "../core/JsonFwd.hpp"
#include "../util/Util.h"
#include "ImageTable.h"
#include "StringTable.h"

#include <optional>
#include <string_view>
#include <vector>

using ObjectEntryIndex = uint16_t;
constexpr const ObjectEntryIndex OBJECT_ENTRY_INDEX_NULL = std::numeric_limits<ObjectEntryIndex>::max();

// First 0xF of rct_object_entry->flags
enum class ObjectType : uint8_t
{
    Ride,
    SmallScenery,
    LargeScenery,
    Walls,
    Banners,
    Paths,
    PathBits,
    SceneryGroup,
    ParkEntrance,
    Water,
    ScenarioText,
    TerrainSurface,
    TerrainEdge,
    Station,
    Music,

    Count,
    None = 255
};

ObjectType& operator++(ObjectType& d, int);

enum OBJECT_SELECTION_FLAGS
{
    OBJECT_SELECTION_FLAG_SELECTED = (1 << 0),
    OBJECT_SELECTION_FLAG_2 = (1 << 1),
    OBJECT_SELECTION_FLAG_IN_USE = (1 << 2),
    // OBJECT_SELECTION_FLAG_REQUIRED = (1 << 3),               // Unused feature
    OBJECT_SELECTION_FLAG_ALWAYS_REQUIRED = (1 << 4),
    OBJECT_SELECTION_FLAG_6 = (1 << 5),
    OBJECT_SELECTION_FLAG_7 = (1 << 6),
    OBJECT_SELECTION_FLAG_8 = (1 << 7),
    OBJECT_SELECTION_FLAG_ALL = 0xFF,
};

#define OBJECT_SELECTION_NOT_SELECTED_OR_REQUIRED 0

enum class ObjectSourceGame : uint8_t
{
    Custom,
    WackyWorlds,
    TimeTwister,
    OpenRCT2Official,
    RCT1,
    AddedAttractions,
    LoopyLandscapes,
    RCT2 = 8
};

#pragma pack(push, 1)
/**
 * Object entry structure.
 * size: 0x10
 */
struct rct_object_entry
{
    union
    {
        uint8_t end_flag; // needed not to read past allocated buffer.
        uint32_t flags;
    };
    union
    {
        char nameWOC[12];
        struct
        {
            char name[8];
            uint32_t checksum;
        };
    };

    std::string_view GetName() const
    {
        return std::string_view(name, std::size(name));
    }

    void SetName(const std::string_view& value);

    ObjectType GetType() const
    {
        return static_cast<ObjectType>(flags & 0x0F);
    }

    void SetType(ObjectType newType)
    {
        flags &= ~0x0F;
        flags |= (static_cast<uint8_t>(newType) & 0x0F);
    }

    std::optional<uint8_t> GetSceneryType() const;

    ObjectSourceGame GetSourceGame() const
    {
        return static_cast<ObjectSourceGame>((flags & 0xF0) >> 4);
    }
};
assert_struct_size(rct_object_entry, 0x10);

struct rct_object_entry_group
{
    void** chunks;
    rct_object_entry* entries;
};
#ifdef PLATFORM_32BIT
assert_struct_size(rct_object_entry_group, 8);
#endif

struct rct_ride_filters
{
    uint8_t category[2];
    uint8_t ride_type;
};
assert_struct_size(rct_ride_filters, 3);

struct rct_object_filters
{
    union
    {
        rct_ride_filters ride;
    };
};
assert_struct_size(rct_object_filters, 3);
#pragma pack(pop)

enum class ObjectGeneration : uint8_t
{
    DAT,
    JSON,
};

struct ObjectEntryDescriptor
{
    ObjectGeneration Generation;
    std::string Identifier; // For JSON objects
    rct_object_entry Entry; // For DAT objects

    ObjectEntryDescriptor()
        : Generation(ObjectGeneration::JSON)
        , Identifier()
        , Entry()
    {
    }

    explicit ObjectEntryDescriptor(const rct_object_entry& newEntry)
    {
        Generation = ObjectGeneration::DAT;
        Entry = newEntry;
    }

    explicit ObjectEntryDescriptor(std::string_view newIdentifier)
    {
        Generation = ObjectGeneration::JSON;
        Identifier = std::string(newIdentifier);
    }
};

struct IObjectRepository;
namespace OpenRCT2
{
    struct IStream;
}
struct ObjectRepositoryItem;
struct rct_drawpixelinfo;

enum class ObjectError : uint32_t
{
    Ok,
    Unknown,
    BadEncoding,
    InvalidProperty,
    BadStringTable,
    BadImageTable,
    UnexpectedEOF,
};

struct IReadObjectContext
{
    virtual ~IReadObjectContext() = default;

    virtual std::string_view GetObjectIdentifier() abstract;
    virtual IObjectRepository& GetObjectRepository() abstract;
    virtual bool ShouldLoadImages() abstract;
    virtual std::vector<uint8_t> GetData(const std::string_view& path) abstract;

    virtual void LogWarning(ObjectError code, const utf8* text) abstract;
    virtual void LogError(ObjectError code, const utf8* text) abstract;
};

#ifdef __WARN_SUGGEST_FINAL_TYPES__
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wsuggest-final-types"
#    pragma GCC diagnostic ignored "-Wsuggest-final-methods"
#endif
class Object
{
private:
    std::string _identifier;
    rct_object_entry _objectEntry{};
    StringTable _stringTable;
    ImageTable _imageTable;
    std::vector<ObjectSourceGame> _sourceGames;
    std::vector<std::string> _authors;
    bool _isJsonObject{};

protected:
    StringTable& GetStringTable()
    {
        return _stringTable;
    }
    const StringTable& GetStringTable() const
    {
        return _stringTable;
    }
    ImageTable& GetImageTable()
    {
        return _imageTable;
    }

    /**
     * Populates the image and string tables from a JSON object
     * @param context
     * @param root JSON node of type object containing image and string info
     * @note root is deliberately left non-const: json_t behaviour changes when const
     */
    void PopulateTablesFromJson(IReadObjectContext* context, json_t& root);

    static rct_object_entry ParseObjectEntry(const std::string& s);

    std::string GetOverrideString(uint8_t index) const;
    std::string GetString(ObjectStringID index) const;
    std::string GetString(int32_t language, ObjectStringID index) const;

public:
    explicit Object(const rct_object_entry& entry);
    virtual ~Object() = default;

    std::string_view GetIdentifier() const
    {
        return _identifier;
    }
    void SetIdentifier(const std::string_view& identifier)
    {
        _identifier = identifier;
    }

    void MarkAsJsonObject()
    {
        _isJsonObject = true;
    }

    bool IsJsonObject() const
    {
        return _isJsonObject;
    };

    // Legacy data structures
    std::string_view GetLegacyIdentifier() const
    {
        return _objectEntry.GetName();
    }
    const rct_object_entry* GetObjectEntry() const
    {
        return &_objectEntry;
    }
    virtual void* GetLegacyData();

    /**
     * @note root is deliberately left non-const: json_t behaviour changes when const
     */
    virtual void ReadJson(IReadObjectContext* /*context*/, json_t& /*root*/)
    {
    }
    virtual void ReadLegacy(IReadObjectContext* context, OpenRCT2::IStream* stream);
    virtual void Load() abstract;
    virtual void Unload() abstract;

    virtual void DrawPreview(rct_drawpixelinfo* /*dpi*/, int32_t /*width*/, int32_t /*height*/) const
    {
    }

    virtual ObjectType GetObjectType() const final
    {
        return _objectEntry.GetType();
    }
    virtual std::string GetName() const;
    virtual std::string GetName(int32_t language) const;

    virtual void SetRepositoryItem(ObjectRepositoryItem* /*item*/) const
    {
    }
    std::vector<ObjectSourceGame> GetSourceGames();
    void SetSourceGames(const std::vector<ObjectSourceGame>& sourceGames);

    const std::vector<std::string>& GetAuthors() const;
    void SetAuthors(const std::vector<std::string>&& authors);

    const ImageTable& GetImageTable() const
    {
        return _imageTable;
    }

    rct_object_entry GetScgWallsHeader();
    rct_object_entry GetScgPathXHeader();
    rct_object_entry CreateHeader(const char name[9], uint32_t flags, uint32_t checksum);

    uint32_t GetNumImages() const
    {
        return GetImageTable().GetCount();
    }
};
#ifdef __WARN_SUGGEST_FINAL_TYPES__
#    pragma GCC diagnostic pop
#endif

extern int32_t object_entry_group_counts[];
extern int32_t object_entry_group_encoding[];

bool object_entry_is_empty(const rct_object_entry* entry);
bool object_entry_compare(const rct_object_entry* a, const rct_object_entry* b);
int32_t object_calculate_checksum(const rct_object_entry* entry, const void* data, size_t dataLength);
bool find_object_in_entry_group(const rct_object_entry* entry, ObjectType* entry_type, ObjectEntryIndex* entryIndex);
void object_create_identifier_name(char* string_buffer, size_t size, const rct_object_entry* object);

const rct_object_entry* object_list_find(rct_object_entry* entry);

void object_entry_get_name_fixed(utf8* buffer, size_t bufferSize, const rct_object_entry* entry);

void* object_entry_get_chunk(ObjectType objectType, ObjectEntryIndex index);
const Object* object_entry_get_object(ObjectType objectType, ObjectEntryIndex index);
