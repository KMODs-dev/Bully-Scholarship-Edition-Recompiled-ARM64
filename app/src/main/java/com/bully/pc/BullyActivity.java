package com.bully.pc;

import android.os.Bundle;
import org.libsdl.app.SDLActivity;

// Tela do jogo: o SDL cria a superficie e chama SDL_main (android_main.cpp). Aberta pelo LauncherActivity,
// que escolhe a pasta do jogo (a instalacao do Bully Scholarship Edition do PC) e as opcoes graficas.
public class BullyActivity extends SDLActivity {
    @Override
    protected String[] getLibraries() { return new String[] {"SDL2", "main"}; }

    @Override
    protected String[] getArguments() {
        // vem do LauncherActivity: pasta de dados do app, pasta do jogo e opcoes ("fps=1 toque=1")
        java.io.File f = getExternalFilesDir(null);
        String dados = f != null ? f.getAbsolutePath() : "/storage/emulated/0/Android/data/com.bully.pc/files";
        android.content.Intent it = getIntent();
        String d = it != null ? it.getStringExtra("dados") : null;
        String p = it != null ? it.getStringExtra("pasta") : null;
        String o = it != null ? it.getStringExtra("opcoes") : null;
        return new String[] {d != null ? d : dados, p != null ? p : dados + "/Bully", o != null ? o : ""};
    }

    @Override
    protected void onCreate(Bundle state) {
        if (android.os.Build.VERSION.SDK_INT >= 28) {
            android.view.WindowManager.LayoutParams lp = getWindow().getAttributes();
            lp.layoutInDisplayCutoutMode = android.view.WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            getWindow().setAttributes(lp);
        }
        super.onCreate(state);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // o runtime nativo (memoria de 4 GB, threads do jogo) nao reinicia no mesmo processo: encerra para o launcher abrir limpo
        System.exit(0);
    }
}
