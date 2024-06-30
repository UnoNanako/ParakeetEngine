#pragma once
#include "WinApp.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <memory>
#include <array>
#include <dxcapi.h>
#include <string>
#include <chrono>

//DirectX基盤
class DirectXCommon {
public:
	void Initialize(std::shared_ptr<WinApp> winApp);// 初期化
	void Finalize(); //Initializeの逆
	void PreDraw();// 描画前
	void PostDraw();// 描画後

	//シェーダーコンパイル関数
	Microsoft::WRL::ComPtr<IDxcBlob> CompileShader(//CompilerするShaderファイルへのパス
		const std::wstring& filePath,
		//Compilerに使用するProfile
		const wchar_t* profile);
	//リソースを作る関数
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(Microsoft::WRL::ComPtr<ID3D12Device> device, size_t sizeInBytes);
	//デスクリプタヒープの添え字をずらす関数
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle();
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle();
	//deviceゲッター
	ID3D12Device* GetDevice() { return mDevice.Get(); }
	ID3D12DescriptorHeap* GetRtvDescriptorHeap() { return mRtvDescriptorHeap.Get(); }
	ID3D12DescriptorHeap* GetSrvDescriptorHeap() { return mSrvDescriptorHeap.Get(); }
	ID3D12DescriptorHeap* GetDsvDescriptorHeap() { return mDsvDescriptorHeap.Get(); }
	ID3D12GraphicsCommandList* GetCommandList() { return mCommandList.Get(); }
	//バックバッファの数を取得
	size_t GetBackBufferCount() const { return mSwapChainResource.size(); }

private:
	//メンバ関数
	//デバイスの初期化
	void CreateDevice();
	//コマンド関連の初期化
	void CreateCommand();
	//スワップチェーンの生成
	void CreateSwapChain(std::shared_ptr<WinApp> winApp);
	//各種デスクリプタヒープの生成
	void CreateEachDescriptorHeap();
	//ディスクリプタヒープを生成する
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
	//レンダーターゲットビューの初期化
	void CreateRenderTargetView();
	//深度バッファの生成
	void ClearDepthBuffer();
	//フェンスの生成
	void CreateFence();
	//ビューポート矩形の初期化
	void InitializeViewport();
	//シザリング矩形の初期化
	void InitializeScissor();
	//DXCコンパイラの生成
	void CreateCompiler();
	//FPS固定初期化
	void InitializeFixFPS();
	//FPS固定更新
	void UpdateFixFPS();

private:
	//メンバ変数
	//DXGIファクトリー
	Microsoft::WRL::ComPtr<IDXGIFactory7> mDxgiFactory;
	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> mDevice;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
	//コマンドアロケータを生成する
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mCommandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvDescriptorHeap;
	uint32_t mDescriptorSizeSRV;
	uint32_t mDescriptorSizeRTV;
	uint32_t mDescriptorSizeDSV;
	//スワップチェーンリソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> mSwapChainResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> mDepthBuffer;
	D3D12_RENDER_TARGET_VIEW_DESC mRtvDesc{};
	Microsoft::WRL::ComPtr<IDxcUtils> mDxcUtils;
	Microsoft::WRL::ComPtr<IDxcCompiler3> mDxcCompiler;
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> mIncludeHandler;
	// RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE mRtvHandles[2];
	// ビューポート
	D3D12_VIEWPORT mViewport{};
	// シザー矩形
	D3D12_RECT mScissorRect{};
	Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
	uint64_t mFenceValue;
	HANDLE mFenceEvent;
	UINT mBackBufferIndex;
	
	uint32_t mSrvDescHeapIndex;

	//記録時間(FPS固定用)
	std::chrono::steady_clock::time_point mReference;
};

