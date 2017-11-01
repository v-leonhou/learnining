SELECT
	@paiming := @paiming + 1 AS pm,
	c.*
FROM
	(
		SELECT
			b.*, wangdian.bianhao
		FROM
			wangdian
		LEFT JOIN (
			SELECT
				count(*) AS count,
				wangdian_bianhao
			FROM
				waybill
			WHERE
				yw_type = 0
			GROUP BY
				wangdian_bianhao
			ORDER BY
				count DESC
		) AS b ON wangdian.bianhao = b.wangdian_bianhao
		ORDER BY
			count DESC
	) AS c,
	(SELECT @paiming := 0) as m
