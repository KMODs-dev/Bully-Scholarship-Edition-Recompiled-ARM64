package com.bully.pc;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.graphics.Typeface;
import android.graphics.drawable.GradientDrawable;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.provider.DocumentsContract;
import android.provider.Settings;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.Spinner;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;

// Launcher: escolhe a pasta do jogo e as opcoes graficas, grava no registro do jogo (registro.txt) e abre o BullyActivity.
public class LauncherActivity extends Activity {
    private static final int REQ_PASTA = 1;
    private static final int REQ_PERM = 2;
    // chave do registro onde o Bully guarda as opcoes de video (HKCU\...\A0, adaptador 0)
    private static final String REG_KEY = "hkcu\\software\\rockstar games\\bully scholarship edition\\a0";

    // o jogo so aceita altura >= 600 e proporcao ate 16:9 (fora disso volta para 800x600)
    private static final int[][] RES = {
        {800, 600}, {1024, 600}, {1066, 600}, {1280, 720}, {1366, 768}, {1600, 900}, {1920, 1080}};
    private static final String[] RES_NOMES = {
        "800 x 600 (4:3, padrão antigo)", "1024 x 600 (quase 16:9)", "1066 x 600 (16:9, recomendado)",
        "1280 x 720 (16:9, HD)", "1366 x 768 (16:9)", "1600 x 900 (16:9, pesado)", "1920 x 1080 (16:9, muito pesado)"};
    private static final String[] SOMBRA_NOMES = {"Desligadas", "Baixas", "Médias", "Altas"};
    private static final String[] FPS_NOMES = {"30 FPS (padrão do jogo)", "60 FPS"};

    private SharedPreferences prefs;
    private TextView txtPasta, txtStatus;
    private Button btnPerm, btnJogar;
    private Spinner spRes, spSombra, spLimite;
    private Switch swFps, swToque, swTela;

    private String pastaPadrao() {
        File f = getExternalFilesDir(null);
        return (f != null ? f.getAbsolutePath() : "/storage/emulated/0/Android/data/com.bully.pc/files") + "/Bully";
    }
    private String dadosApp() {
        File f = getExternalFilesDir(null);
        return f != null ? f.getAbsolutePath() : "/storage/emulated/0/Android/data/com.bully.pc/files";
    }

    @Override
    protected void onCreate(Bundle state) {
        super.onCreate(state);
        prefs = getSharedPreferences("launcher", MODE_PRIVATE);
        new File(dadosApp()).mkdirs();
        setContentView(montarTela());
        atualizar();
    }

    @Override
    protected void onResume() { super.onResume(); atualizar(); }

    // ------------------------------------------------------------------ tela
    private int dp(float v) { return (int) (v * getResources().getDisplayMetrics().density + 0.5f); }

    private TextView rotulo(String s, float tam, int cor, boolean negrito) {
        TextView t = new TextView(this);
        t.setText(s); t.setTextSize(tam); t.setTextColor(cor);
        if (negrito) t.setTypeface(Typeface.DEFAULT_BOLD);
        return t;
    }
    private LinearLayout cartao(LinearLayout pai, String titulo) {
        LinearLayout c = new LinearLayout(this);
        c.setOrientation(LinearLayout.VERTICAL);
        c.setPadding(dp(16), dp(12), dp(16), dp(14));
        GradientDrawable bg = new GradientDrawable(); bg.setColor(0xFF1E2230); bg.setCornerRadius(dp(10));
        c.setBackground(bg);
        LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        lp.topMargin = dp(12);
        pai.addView(c, lp);
        c.addView(rotulo(titulo, 15, 0xFFFFC94A, true));
        return c;
    }
    private Button botao(String s, int cor) {
        Button b = new Button(this);
        b.setText(s); b.setAllCaps(false); b.setTextColor(Color.WHITE);
        GradientDrawable bg = new GradientDrawable(); bg.setColor(cor); bg.setCornerRadius(dp(8));
        b.setBackground(bg);
        return b;
    }
    private Spinner lista(String[] itens, int sel, final String chave) {
        Spinner s = new Spinner(this);
        ArrayAdapter<String> ad = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, itens) {
            @Override public View getView(int p, View v, ViewGroup g) { TextView t = (TextView) super.getView(p, v, g); t.setTextColor(Color.WHITE); return t; }
        };
        ad.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        s.setAdapter(ad);
        s.setSelection(Math.max(0, Math.min(sel, itens.length - 1)));
        s.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override public void onItemSelected(AdapterView<?> a, View v, int p, long id) { prefs.edit().putInt(chave, p).apply(); }
            @Override public void onNothingSelected(AdapterView<?> a) {}
        });
        return s;
    }
    private Switch chave(String s, boolean v, final String k) {
        Switch w = new Switch(this);
        w.setText(s); w.setTextColor(Color.WHITE); w.setTextSize(14); w.setChecked(v);
        w.setPadding(0, dp(8), 0, dp(4));
        w.setOnCheckedChangeListener((b, c) -> prefs.edit().putBoolean(k, c).apply());
        return w;
    }

    private View montarTela() {
        ScrollView sv = new ScrollView(this);
        sv.setBackgroundColor(0xFF12141C);
        LinearLayout raiz = new LinearLayout(this);
        raiz.setOrientation(LinearLayout.VERTICAL);
        raiz.setPadding(dp(20), dp(16), dp(20), dp(24));
        sv.addView(raiz);

        raiz.addView(rotulo("Bully: Scholarship Edition", 24, Color.WHITE, true));
        raiz.addView(rotulo("Versão de PC recompilada para Android", 13, 0xFF9AA0B4, false));

        // pasta do jogo
        LinearLayout cp = cartao(raiz, "Pasta do jogo");
        txtPasta = rotulo("", 13, Color.WHITE, false); txtPasta.setPadding(0, dp(6), 0, dp(2));
        cp.addView(txtPasta);
        txtStatus = rotulo("", 13, Color.WHITE, false);
        cp.addView(txtStatus);
        LinearLayout lb = new LinearLayout(this); lb.setOrientation(LinearLayout.HORIZONTAL); lb.setPadding(0, dp(10), 0, 0);
        Button bEsc = botao("Escolher pasta", 0xFF3A4260);
        bEsc.setOnClickListener(v -> escolherPasta());
        Button bPad = botao("Usar pasta padrão", 0xFF3A4260);
        bPad.setOnClickListener(v -> { prefs.edit().putString("pasta", pastaPadrao()).apply(); atualizar(); });
        LinearLayout.LayoutParams wl = new LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.WRAP_CONTENT, 1);
        wl.rightMargin = dp(8);
        lb.addView(bEsc, wl);
        lb.addView(bPad, new LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.WRAP_CONTENT, 1));
        cp.addView(lb);
        btnPerm = botao("Permitir acesso aos arquivos", 0xFF8A5A12);
        btnPerm.setOnClickListener(v -> pedirPermissao());
        LinearLayout.LayoutParams pl = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        pl.topMargin = dp(8);
        cp.addView(btnPerm, pl);

        // graficos
        LinearLayout cg = cartao(raiz, "Gráficos");
        cg.addView(rotulo("Resolução interna", 13, 0xFF9AA0B4, false));
        spRes = lista(RES_NOMES, prefs.getInt("res2", 2), "res2");
        cg.addView(spRes);
        cg.addView(rotulo("Quanto maior, mais nítido e mais pesado para a GPU. As opções 16:9 ocupam mais da tela.", 12, 0xFF6F768C, false));
        TextView ts = rotulo("Sombras", 13, 0xFF9AA0B4, false); ts.setPadding(0, dp(10), 0, 0);
        cg.addView(ts);
        spSombra = lista(SOMBRA_NOMES, prefs.getInt("sombra", 0), "sombra");
        cg.addView(spSombra);
        cg.addView(rotulo("Sombras dinâmicas custam FPS.", 12, 0xFF6F768C, false));
        TextView tl = rotulo("Limite de FPS", 13, 0xFF9AA0B4, false); tl.setPadding(0, dp(10), 0, 0);
        cg.addView(tl);
        spLimite = lista(FPS_NOMES, prefs.getInt("limite", 0), "limite");
        cg.addView(spLimite);
        cg.addView(rotulo("60 FPS só vale se o aparelho aguentar; minigames que pedem outro limite continuam com o deles.", 12, 0xFF6F768C, false));

        // tela
        LinearLayout ct = cartao(raiz, "Tela");
        swFps = chave("Mostrar FPS", prefs.getBoolean("fps", true), "fps");
        ct.addView(swFps);
        swToque = chave("Controles na tela (toque)", prefs.getBoolean("toque", true), "toque");
        ct.addView(swToque);
        swTela = chave("Tela cheia (estica a imagem, sem faixas pretas)", prefs.getBoolean("tela", false), "tela");
        ct.addView(swTela);
        ct.addView(rotulo("Com um controle conectado, os botões na tela somem sozinhos.", 12, 0xFF6F768C, false));

        btnJogar = botao("JOGAR", 0xFF2E8B57);
        btnJogar.setTextSize(18); btnJogar.setTypeface(Typeface.DEFAULT_BOLD);
        btnJogar.setOnClickListener(v -> jogar());
        LinearLayout.LayoutParams jl = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, dp(56));
        jl.topMargin = dp(18);
        raiz.addView(btnJogar, jl);

        TextView rod = rotulo("Log: " + dadosApp() + "/bully-log.txt", 11, 0xFF6F768C, false);
        rod.setPadding(0, dp(10), 0, 0); rod.setGravity(Gravity.CENTER);
        raiz.addView(rod);
        return sv;
    }

    // ------------------------------------------------------------------ pasta e permissao
    private String pasta() { return prefs.getString("pasta", pastaPadrao()); }

    private boolean dentroDoApp(String p) {
        File f = getExternalFilesDir(null);
        return f != null && p.startsWith(f.getParentFile().getAbsolutePath());
    }
    private boolean temPermissao() {
        if (Build.VERSION.SDK_INT >= 30) return Environment.isExternalStorageManager();
        return checkSelfPermission(android.Manifest.permission.WRITE_EXTERNAL_STORAGE) == android.content.pm.PackageManager.PERMISSION_GRANTED;
    }
    private boolean precisaPermissao() { return !dentroDoApp(pasta()) && !temPermissao(); }

    private File acharExe(String p) {
        File d = new File(p);
        String[] nomes = d.list();
        if (nomes == null) return null;
        for (String n : nomes) if (n.equalsIgnoreCase("Bully.exe")) return new File(d, n);
        return null;
    }

    private void atualizar() {
        if (txtPasta == null) return;
        String p = pasta();
        txtPasta.setText(p);
        boolean perm = precisaPermissao();
        btnPerm.setVisibility(perm ? View.VISIBLE : View.GONE);
        if (perm) {
            txtStatus.setText("Falta permitir o acesso aos arquivos para ler esta pasta.");
            txtStatus.setTextColor(0xFFFFB347);
        } else if (acharExe(p) != null) {
            txtStatus.setText("Bully.exe encontrado.");
            txtStatus.setTextColor(0xFF6FD08C);
        } else {
            txtStatus.setText("Bully.exe não encontrado. Escolha a pasta com a instalação do PC (onde fica o Bully.exe).");
            txtStatus.setTextColor(0xFFFF6B6B);
        }
    }

    private void escolherPasta() {
        try {
            startActivityForResult(new Intent(Intent.ACTION_OPEN_DOCUMENT_TREE), REQ_PASTA);
        } catch (Exception e) {
            Toast.makeText(this, "Este aparelho não tem seletor de pastas.", Toast.LENGTH_LONG).show();
        }
    }

    // content://.../tree/primary:Jogos/Bully -> /storage/emulated/0/Jogos/Bully (cartao SD: /storage/XXXX-XXXX/...)
    private String caminhoDaArvore(Uri uri) {
        try {
            String id = DocumentsContract.getTreeDocumentId(uri);
            int i = id.indexOf(':');
            String vol = i >= 0 ? id.substring(0, i) : id, rel = i >= 0 ? id.substring(i + 1) : "";
            String base = "primary".equalsIgnoreCase(vol) ? Environment.getExternalStorageDirectory().getAbsolutePath() : "/storage/" + vol;
            return rel.isEmpty() ? base : base + "/" + rel;
        } catch (Exception e) {
            return null;
        }
    }

    @Override
    protected void onActivityResult(int req, int res, Intent data) {
        super.onActivityResult(req, res, data);
        if (req == REQ_PASTA && res == RESULT_OK && data != null && data.getData() != null) {
            String p = caminhoDaArvore(data.getData());
            if (p == null) { Toast.makeText(this, "Não consegui usar essa pasta. Tente uma pasta da memória interna.", Toast.LENGTH_LONG).show(); return; }
            // se escolheram a pasta de cima, procura uma subpasta com o Bully.exe
            if (acharExe(p) == null) {
                File[] subs = new File(p).listFiles();
                if (subs != null) for (File s : subs) if (s.isDirectory() && acharExe(s.getAbsolutePath()) != null) { p = s.getAbsolutePath(); break; }
            }
            prefs.edit().putString("pasta", p).apply();
            atualizar();
            if (precisaPermissao()) pedirPermissao();
        }
    }

    private void pedirPermissao() {
        if (Build.VERSION.SDK_INT >= 30) {
            try {
                startActivity(new Intent(Settings.ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION, Uri.parse("package:" + getPackageName())));
            } catch (Exception e) {
                startActivity(new Intent(Settings.ACTION_MANAGE_ALL_FILES_ACCESS_PERMISSION));
            }
        } else {
            requestPermissions(new String[] {android.Manifest.permission.READ_EXTERNAL_STORAGE, android.Manifest.permission.WRITE_EXTERNAL_STORAGE}, REQ_PERM);
        }
    }

    @Override
    public void onRequestPermissionsResult(int req, String[] perms, int[] res) { atualizar(); }

    // ------------------------------------------------------------------ registro do jogo e inicio
    private static String dwordHex(int v) {
        return String.format("%02x%02x%02x%02x", v & 0xFF, (v >> 8) & 0xFF, (v >> 16) & 0xFF, (v >>> 24) & 0xFF);
    }

    // mesmo formato que o runtime le e grava: chave<TAB>nome<TAB>tipo<TAB>hex
    private void gravarRegistro(int w, int h, int sombra) throws Exception {
        File f = new File(dadosApp(), "registro.txt");
        List<String> linhas = new ArrayList<>();
        String[] nossos = {"resw", "resh", "aa", "vs", "sha", "win"};
        if (f.exists()) {
            try (BufferedReader r = new BufferedReader(new FileReader(f))) {
                String l;
                while ((l = r.readLine()) != null) {
                    String[] c = l.split("\t");
                    boolean meu = false;
                    if (c.length >= 2 && c[0].equals(REG_KEY)) for (String n : nossos) if (c[1].equals(n)) meu = true;
                    if (!meu && !l.trim().isEmpty()) linhas.add(l);
                }
            }
        }
        linhas.add(REG_KEY + "\tresw\t4\t" + dwordHex(w));
        linhas.add(REG_KEY + "\tresh\t4\t" + dwordHex(h));
        linhas.add(REG_KEY + "\taa\t4\t" + dwordHex(1));
        linhas.add(REG_KEY + "\tvs\t4\t" + dwordHex(0));
        linhas.add(REG_KEY + "\tsha\t4\t" + dwordHex(sombra));
        linhas.add(REG_KEY + "\twin\t4\t" + dwordHex(0));
        try (FileWriter wr = new FileWriter(f)) { for (String l : linhas) wr.write(l + "\n"); }
    }

    private void jogar() {
        String p = pasta();
        if (precisaPermissao()) { pedirPermissao(); return; }
        if (acharExe(p) == null) { Toast.makeText(this, "Bully.exe não encontrado nessa pasta.", Toast.LENGTH_LONG).show(); return; }
        int r = Math.max(0, Math.min(spRes.getSelectedItemPosition(), RES.length - 1));
        int s = Math.max(0, Math.min(spSombra.getSelectedItemPosition(), 3));
        try {
            gravarRegistro(RES[r][0], RES[r][1], s);
        } catch (Exception e) {
            Toast.makeText(this, "Não consegui salvar as opções: " + e.getMessage(), Toast.LENGTH_LONG).show();
        }
        Intent it = new Intent(this, BullyActivity.class);
        it.putExtra("dados", dadosApp());
        it.putExtra("pasta", p);
        it.putExtra("opcoes", "fps=" + (swFps.isChecked() ? 1 : 0) + " toque=" + (swToque.isChecked() ? 1 : 0)
                + " limite=" + (spLimite.getSelectedItemPosition() == 1 ? 60 : 30)
                + " tela=" + (swTela.isChecked() ? 1 : 0));
        startActivity(it);
        finish();
    }
}
