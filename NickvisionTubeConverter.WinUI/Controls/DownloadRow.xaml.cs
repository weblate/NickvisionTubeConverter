using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using NickvisionTubeConverter.Shared.Controls;
using NickvisionTubeConverter.Shared.Helpers;
using NickvisionTubeConverter.Shared.Models;
using System;
using System.Threading.Tasks;
using Windows.System;

namespace NickvisionTubeConverter.WinUI.Controls;

/// <summary>
/// A row for managing a download
/// </summary>
public sealed partial class DownloadRow : UserControl, IDownloadRowControl
{
    private readonly Localizer _localizer;
    private readonly Download _download;
    private bool? _previousEmbedMetadata;
    private bool _wasStopped;

    public bool IsDone => _download.IsDone;

    /// <summary>
    /// Constructs a DownloadRow
    /// </summary>
    /// <param name="localizer">Localizer</param>
    /// <param name="download">Download</param>
    public DownloadRow(Localizer localizer, Download download)
    {
        InitializeComponent();
        _localizer = localizer;
        _download = download;
        _previousEmbedMetadata = null;
        _wasStopped = false;
        //Localize Strings
        ToolTipService.SetToolTip(BtnStop, _localizer["StopDownload"]);
        ToolTipService.SetToolTip(BtnRetry, _localizer["RetryDownload"]);
        ToolTipService.SetToolTip(BtnOpenSaveFolder, _localizer["OpenSaveFolder"]);
        //Load
        LblUrl.Text = _download.VideoUrl;
    }

    /// <summary>
    /// Starts the download
    /// </summary>
    /// <param name="embedMetadata">Whether or not to embed video metadata</param>
    public async Task StartAsync(bool embedMetadata)
    {
        if (_previousEmbedMetadata == null)
        {
            _previousEmbedMetadata = embedMetadata;
        }
        _wasStopped = false;
        Icon.Glyph = "\uE118";
        LblFilename.Text = _download.Filename;
        LblStatus.Text = _localizer["DownloadState", "Preparing"];
        BtnStop.Visibility = Visibility.Visible;
        BtnRetry.Visibility = Visibility.Collapsed;
        BtnOpenSaveFolder.Visibility = Visibility.Collapsed;
        ProgBar.Value = 0;
        var success = await _download.RunAsync(embedMetadata, (state) =>
        {
            switch (state.Status)
            {
                case DownloadProgressStatus.Downloading:
                    App.MainWindow!.DispatcherQueue.TryEnqueue(() =>
                    {
                        ProgBar.IsIndeterminate = false;
                        ProgBar.Value = state.Progress;
                        LblStatus.Text = string.Format(_localizer["DownloadState", "Downloading"], state.Progress * 100, state.Speed);
                    });
                    break;
                case DownloadProgressStatus.Processing:
                    App.MainWindow!.DispatcherQueue.TryEnqueue(() =>
                    {
                        LblStatus.Text = _localizer["DownloadState", "Processing"];
                        ProgBar.IsIndeterminate = true;
                    });
                    break;
            }
        });
        if (!_wasStopped)
        {
            Icon.Glyph = success ? "\uE10B" : "\uE10A";
            ProgBar.IsIndeterminate = false;
            ProgBar.Value = 1;
            LblStatus.Text = success ? _localizer["Success"] : _localizer["Error"];
            BtnStop.Visibility = Visibility.Collapsed;
            BtnRetry.Visibility = !success ? Visibility.Visible : Visibility.Collapsed;
            BtnOpenSaveFolder.Visibility = success ? Visibility.Visible : Visibility.Collapsed;
        }
    }

    /// <summary>
    /// Stops the download
    /// </summary>
    public void Stop()
    {
        _wasStopped = true;
        _download.Stop();
        Icon.Glyph = "\uE10A";
        ProgBar.IsIndeterminate = false;
        ProgBar.Value = 1;
        LblStatus.Text = _localizer["Stopped"];
        BtnStop.Visibility = Visibility.Collapsed;
        BtnRetry.Visibility = Visibility.Visible;
        BtnOpenSaveFolder.Visibility = Visibility.Collapsed;
    }

    /// <summary>
    /// Occurs when the stop button is clicked
    /// </summary>
    /// <param name="sender">object</param>
    /// <param name="e">RoutedEventArgs</param>
    private void BtnStop_Click(object sender, RoutedEventArgs e) => Stop();

    /// <summary>
    /// Occurs when the retry button is clicked
    /// </summary>
    /// <param name="sender">object</param>
    /// <param name="e">RoutedEventArgs</param>
    private async void BtnRetry_Click(object sender, RoutedEventArgs e) => await StartAsync(_previousEmbedMetadata ?? false);

    /// <summary>
    /// Occurs when the open save folder button is clicked
    /// </summary>
    /// <param name="sender">object</param>
    /// <param name="e">RoutedEventArgs</param>
    private async void BtnOpenSaveFolder_Click(object sender, RoutedEventArgs e) => await Launcher.LaunchFolderPathAsync(_download.SaveFolder);
}
