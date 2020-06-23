/* Declarations */
void write_simresult_to_csv(algoticks_simresult simresult);
void chomp(char *s);
algoticks_benchmarkconfig parse_benchmark_from_json(char *filename);
algoticks_settings parse_settings_from_json(char *filename);
algoticks_config parse_config_from_json(char *filename);
algoticks_config filter_boundaries(algoticks_config config, int is_short);
int is_target_hit(algoticks_dashboard dashboard, float target);
int is_stoploss_hit(algoticks_dashboard dashboard, float stoploss);
float brokerage_calc();