//
// MainPage.xaml.cpp
// MainPage 클래스의 구현입니다.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ProjectN;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// 빈 페이지 항목 템플릿에 대한 설명은 https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x412에 나와 있습니다.

MainPage::MainPage()
{
	InitializeComponent();
}



// 폴더 경로를 입력받아 표시

using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;

void MainPage::SelectFolder_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto picker = ref new FolderPicker();
    picker->SuggestedStartLocation = PickerLocationId::Desktop;
    picker->FileTypeFilter->Append("*");
    picker->ViewMode = PickerViewMode::List;

    // Show the folder picker
    concurrency::create_task(picker->PickSingleFolderAsync()).then([this](StorageFolder^ folder)
    {
        if (folder != nullptr)
        {
            // Folder selected, display the path
            this->FolderPathTextBox->Text = folder->Path;
            this->SelectedFolderPathTextBlock->Text = "Selected Folder: " + folder->Path;
        }
        else
        {
            // Operation cancelled
            this->SelectedFolderPathTextBlock->Text = "No folder selected.";
        }
    });
}



// 폴더 경로의 파일들의 파일명 표시

#include <memory>

using namespace Windows::UI::Core;

