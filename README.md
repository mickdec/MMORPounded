<!-- <div align="center">
  <img src="https://raw.githubusercontent.com/mickdec/MMORPounded/master/READMERES/MMORP-200x200.png" />
</div> -->
<div align="center">
  <h1 align="center">MMORPounded</h1>
  <i align="center">A toolkit for exploiting winsock2.</i>
</div>

<h2>REQUIREMENTS</h2>
<ul>
<li>1. Windows.
<li>2. <a href="https://visualstudio.microsoft.com/fr/thank-you-downloading-visual-studio/?sku=Community&rel=16">VS2019</a>.
<li>3. <a href="https://developer.microsoft.com/fr-fr/windows/downloads/windows-10-sdk">Win 10 SDK</a>.
<li>(Optionnal but recommended 4. <a href="https://debugger.immunityinc.com/ID_register.py">A debugger</a>.)
</ul>
<h2>DISCLAIMER</h2>
<p><i>
This tool is meant to be used only for benevolent purposes.
<br>I am in no way responsible for your actions and the use you can make of that tool.
</i><p>
<h2>WHAT THIS TOOLKIT DOES</h2>
<p>
This tool kit contains all you need to exploit winsock in windows applications.
<hr>
VS2019 will install the <b>"Developer Command Prompt for VS 2019"</b> who will be used to found if the target program use winsock and all the function you want to hook :
<div align="center">
  <img src="https://raw.githubusercontent.com/mickdec/MMORPounded/master/READMERES/VS2019CMD.png" />
</div>
<hr>
<b>Arwin</b>, is used to found adresses of winsock function in ws2_32.dll :
<div align="center">
  <img src="https://raw.githubusercontent.com/mickdec/MMORPounded/master/READMERES/Arwin.png" />
</div>
<hr>
<b>VS2019</b> is used to develop your cpp DLL and DetoursInjector (The DLL injector) :
<div align="center">
  <img src="https://raw.githubusercontent.com/mickdec/MMORPounded/master/READMERES/VS2019.png" />
</div>
<hr>
Once all is done, builded as you wish and all, you can start to hooking process by inject the DLL :
<div align="center">
  <img src="https://raw.githubusercontent.com/mickdec/MMORPounded/master/READMERES/INJECT.png" />
</div>

</p>
<h2>USAGE</h2>
I will not show any example of exploitation, just giving you some ints with this repo.
<br>
have fun to found it by yourself :)
<br>
My research is following this pretty good <a href="https://resources.infosecinstitute.com/api-hooking-detours/">tutorial</a> thanks to him.
<p>
