set nocompatible          "不要兼容vi
filetype off              "必须的设置：

"Color Settings {
"set colorcolumn=120           "彩色显示第85列
set t_Co=256                 "设置256色显示
set background=dark          "使用color solarized
set cursorline               "设置光标高亮显示
"set cursorcolumn             "光标垂直高亮
set ttyfast
""set ruler
set backspace=indent,eol,start
" "colorscheme solarized
" "colorscheme vividchalk
" "colorscheme desert256
colorscheme ron


let g:solarized_termtrans  = 1
let g:solarized_termcolors = 256
let g:solarized_contrast   = "high"
let g:solarized_visibility = "high"
"}

"tab setting {
set tabstop=4
set shiftwidth=4
set softtabstop=4
"set expandtab
"}

set fileencodings=ucs-bom,utf-8,cp936,gb18030,big5,euc-jp,euc-kr,latin1
set scrolloff=3
set fenc=utf-8
set autoindent
set hidden
"set encoding=utf-8

"set laststatus=2
set number                                     "显示行号
"set undofile                                  "无限undo
set wrap									   "自动换行
"set nowrap                                    "禁止自动换行
"autocmd! bufwritepost _vimrc source %         "自动载入配置文件不需要重启

"相对行号 要想相对行号起作用要放在显示行号后面
""set relativenumber
"GUI界面里的字体，默认有抗锯齿
set guifont=Inconsolata:h15
"将-连接符也设置为单词
set isk+=-

" Highlight trailing white-spaces
let c_space_errors=1
autocmd Syntax * syn match ExtraWhitespace /\s\+$/
" "set t_Co=256

"关掉智能补全时的预览窗口，这样可以防止闪屏现象
set completeopt=longest,menu

"默认无备份
set nobackup
set nowritebackup

"高亮搜索的关键字
set hlsearch


"放置在Bundle的设置后，防止意外BUG
filetype plugin indent on
set nocp

"打开语法高亮显示功能
syntax enable
syntax on

"mouse support for terminal
"set mouse=n

" 状态栏
set laststatus=2      " 总是显示状态栏
highlight StatusLine cterm=bold ctermfg=yellow ctermbg=blue


"在buffer间切换不需要存盘
":set hidden
"set error format for gcc, and ignore warning message
":set efm=%f:%l:error

"auto save project view,! for force overwrite
":au VimLeave * mksession! session.vim
":au VimLeave * wviminfo! viminfo


"下次打开文件可回到上次退出时的光标位置
autocmd BufReadPost *
     \ if line("'\"") > 0 && line("'\"") <= line("$") |
     \ exe "normal g`\"" |
     \ endif

"设置MiniBufExpl
let g:miniBufExplMapWindowNavVim = 1 
let g:miniBufExplMapWindowNavArrows = 1 
let g:miniBufExplMapCTabSwitchBufs = 1 
let g:miniBufExplModSelTarget = 1 
let g:miniBufExplorerMoreThanOne = 0 " Very important
let g:miniBufExplMaxHeight = 5

"设置Taglist
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1
let Tlist_Use_Right_Window=0


"设置SuperTab，用tab键打开cppcomplet的自动补全功能。
"set a value for fear that when  edit txt file, popup "E764 omnifunc not set"
set omnifunc=ccomplete#Complete
let g:SuperTabRetainCompletionType=2
let g:SuperTabDefaultCompletionType="<C-X><C-O>"
"插入模式下shift-tab取消自动补全
let g:SuperTabMappingForward = "<tab>"
let g:SuperTabMappingBackward= "<s-tab>"



if has("cscope")
	set csprg=/usr/bin/cscope " 指定用来执行cscope的命令
	set csto=0 " 设置cstag命令查找次序：0先找cscope数据库再找标签文件；1先找标签文件再找cscope数据库
	set cst " 同时搜索cscope数据库和标签文件
	set nocsverb
	if filereadable("cscope.out") " 若当前目录下存在cscope数据库，添加该数据库到vim
		cs add cscope.out
		autocmd vimenter * TrinityToggleAll
	elseif $CSCOPE_DB != "" " 否则只要环境变量CSCOPE_DB不为空，则添加其指定的数据库到vim
		cs add $CSCOPE_DB
	endif
	set csverb
endif

"map hotkey for cscope
nmap e :cs find e <cword><CR>
nmap s :cs find s <cword><CR>
"nmap w :cs find c <cword><CR>
nmap f :cs find f <cfile><CR>

" prompt for which tag if multiple tags found
:noremap  <C-]>  g<C-]>


nnoremap <Tab> :bnext<CR>
nnoremap <S-Tab> :bprevious<CR>



" // Set the height of Source Explorer window
let g:SrcExpl_winHeight = 8

" // Set 100 ms for refreshing the Source Explorer
let g:SrcExpl_refreshTime = 100

" // Set "Enter" key to jump into the exact definition context
" let g:SrcExpl_jumpKey = "<ENTER>"

" // Set "Space" key for back from the definition context
let g:SrcExpl_gobackKey = "<SPACE>"

" // In order to Avoid conflicts, the Source Explorer should know what plugins
" // are using buffers. And you need add their bufname into the list below
" // according to the command ":buffers!"
let g:SrcExpl_pluginList = [
		\ "-MiniBufExplorer-",
        \ "__Tag_List__",
        \ "_NERD_tree_",
        \ "Source_Explorer"
    \ ]

" // Enable/Disable the local definition searching, and note that this is not
" // guaranteed to work, the Source Explorer doesn't check the syntax for now.
" // It only searches for a match with the keyword according to command 'gd'
let g:SrcExpl_searchLocalDef = 1

" // Do not let the Source Explorer update the tags file when opening
let g:SrcExpl_isUpdateTags = 0

" // Use 'Exuberant Ctags' with '--sort=foldcase -R .' or '-L cscope.files' to
" //  create/update a tags file
let g:SrcExpl_updateTagsCmd = "ctags --sort=foldcase -R ."

" // Set "<F5>" key for updating the tags file artificially
let g:SrcExpl_updateTagsKey = "<F5>"

" // Do not let the Source Explorer update the tags file when opening
let g:SrcExpl_isUpdateCscope = 0

" //  create/update a cscope file
let g:SrcExpl_updateCscopeCmd = "cscope -Rbkq"

" // Set "<F6>" key for updating the tags file artificially
let g:SrcExpl_updateCscopeKey = "<F6>"

"
" "Update tags
nmap <F5>  :SrcExplUpdateTags<CR>
"
" "Update cscope
nmap <F6>  :SrcExplUpdateCscope<CR>

"
" Open and close all the three plugins on the same time
nmap <F8>   :TrinityToggleAll<CR>
"
" " Open and close the taglist.vim separately
nmap <F9>  :TrinityToggleTagList<CR>
"
" " Open and close the srcexpl.vim separately
nmap <F10>  :TrinityToggleSourceExplorer<CR>
"
" " Open and close the NERD_tree.vim separately
nmap <F11>  :TrinityToggleNERDTree<CR>
"
" " Open and close the MinibufExpl.vim separately
nmap <F12>  :TrinityToggleMiniBufExplorer<CR>
"nmap <F12>  :TMiniBufExplorer<CR>
"
"
"
