#include "models/downloaderoptions.h"
#include <libnick/system/environment.h>

using namespace Nickvision::System;

namespace Nickvision::TubeConverter::Shared::Models
{
    DownloaderOptions::DownloaderOptions()
        : m_overwriteExistingFiles{ true },
        m_maxNumberOfActiveDownloads{ 5 },
        m_limitCharacters{ Environment::getOperatingSystem() == OperatingSystem::Windows },
        m_includeAutoGeneratedSubtitles{ true },
        m_preferredVideoCodec{ VideoCodec::Any },
        m_useAria{ false },
        m_ariaMaxConnectionsPerServer{ 16 },
        m_ariaMinSplitSize{ 20 },
        m_speedLimit{ 1024 },
        m_proxyUrl{ "" },
        m_cookiesBrowser{ Browser::None },
        m_youTubeSponsorBlock{ false },
        m_embedMetadata{ true },
        m_cropAudioThumbnails{ false },
        m_removeSourceData{ false },
        m_embedChapters{ false },
        m_embedSubtitles{ true },
        m_ffmpegArgs{ "" }
    {
        
    }

    bool DownloaderOptions::getOverwriteExistingFiles() const
    {
        return m_overwriteExistingFiles;
    }

    void DownloaderOptions::setOverwriteExistingFiles(bool overwrite)
    {
        m_overwriteExistingFiles = overwrite;
    }

    int DownloaderOptions::getMaxNumberOfActiveDownloads() const
    {
        return m_maxNumberOfActiveDownloads;
    }

    void DownloaderOptions::setMaxNumberOfActiveDownloads(int max)
    {
        if(max < 1 || max > 10)
        {
            max = 5;
        }
        m_maxNumberOfActiveDownloads = max;
    }

    bool DownloaderOptions::getLimitCharacters() const
    {
        return m_limitCharacters;
    }

    void DownloaderOptions::setLimitCharacters(bool limit)
    {
        m_limitCharacters = limit;
    }

    bool DownloaderOptions::getIncludeAutoGeneratedSubtitles() const
    {
        return m_includeAutoGeneratedSubtitles;
    }

    void DownloaderOptions::setIncludeAutoGeneratedSubtitles(bool include)
    {
        m_includeAutoGeneratedSubtitles = include;
    }

    VideoCodec DownloaderOptions::getPreferredVideoCodec() const
    {
        return m_preferredVideoCodec;
    }

    void DownloaderOptions::setPreferredVideoCodec(VideoCodec codec)
    {
        m_preferredVideoCodec = codec;
    }

    bool DownloaderOptions::getUseAria() const
    {
        return m_useAria;
    }

    void DownloaderOptions::setUseAria(bool useAria)
    {
        m_useAria = useAria;
    }

    int DownloaderOptions::getAriaMaxConnectionsPerServer() const
    {
        return m_ariaMaxConnectionsPerServer;
    }

    void DownloaderOptions::setAriaMaxConnectionsPerServer(int maxConnections)
    {
        if(maxConnections < 1 || maxConnections > 16)
        {
            maxConnections = 16;
        }
        m_ariaMaxConnectionsPerServer = maxConnections;
    }

    int DownloaderOptions::getAriaMinSplitSize() const
    {
        return m_ariaMinSplitSize;
    }

    void DownloaderOptions::setAriaMinSplitSize(int minSplitSize)
    {
        if(minSplitSize < 1 || minSplitSize > 1024)
        {
            minSplitSize = 20;
        }
        m_ariaMinSplitSize = minSplitSize;
    }

    unsigned int DownloaderOptions::getSpeedLimit() const
    {
        return m_speedLimit;
    }

    void DownloaderOptions::setSpeedLimit(unsigned int speedLimit)
    {
        if(speedLimit < 512 || speedLimit > 10240)
        {
            speedLimit = 1024;
        }
        m_speedLimit = speedLimit;
    }

    const std::string& DownloaderOptions::getProxyUrl() const
    {
        return m_proxyUrl;
    }

    void DownloaderOptions::setProxyUrl(const std::string& proxyUrl)
    {
        m_proxyUrl = proxyUrl;
    }

    Browser DownloaderOptions::getCookiesBrowser() const
    {
        return m_cookiesBrowser;
    }

    void DownloaderOptions::setCookiesBrowser(Browser browser)
    {
        m_cookiesBrowser = browser;
    }

    const std::filesystem::path& DownloaderOptions::getCookiesPath() const
    {
        return m_cookiesPath;
    }

    void DownloaderOptions::setCookiesPath(const std::filesystem::path& path)
    {
        m_cookiesPath = path;
    }

    bool DownloaderOptions::getYouTubeSponsorBlock() const
    {
        return m_youTubeSponsorBlock;
    }

    void DownloaderOptions::setYouTubeSponsorBlock(bool sponsorBlock)
    {
        m_youTubeSponsorBlock = sponsorBlock;
    }

    bool DownloaderOptions::getEmbedMetadata() const
    {
        return m_embedMetadata;
    }

    void DownloaderOptions::setEmbedMetadata(bool embedMetadata)
    {
        m_embedMetadata = embedMetadata;
    }

    bool DownloaderOptions::getCropAudioThumbnails() const
    {
        return m_cropAudioThumbnails;
    }

    void DownloaderOptions::setCropAudioThumbnails(bool cropAudioThumbnails)
    {
        m_cropAudioThumbnails = cropAudioThumbnails;
    }

    bool DownloaderOptions::getRemoveSourceData() const
    {
        return m_removeSourceData;
    }

    void DownloaderOptions::setRemoveSourceData(bool removeSourceData)
    {
        m_removeSourceData = removeSourceData;
    }

    bool DownloaderOptions::getEmbedChapters() const
    {
        return m_embedChapters;
    }

    void DownloaderOptions::setEmbedChapters(bool embedChapters)
    {
        m_embedChapters = embedChapters;
    }

    bool DownloaderOptions::getEmbedSubtitles() const
    {
        return m_embedSubtitles;
    }

    void DownloaderOptions::setEmbedSubtitles(bool embedSubtitles)
    {
        m_embedSubtitles = embedSubtitles;
    }
    
    const std::string& DownloaderOptions::getFFmpegArgs() const
    {
        return m_ffmpegArgs;
    }

    void DownloaderOptions::setFFmpegArgs(const std::string& ffmpegArgs)
    {
        m_ffmpegArgs = ffmpegArgs;
    }
}